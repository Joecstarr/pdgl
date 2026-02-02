set export

@_default:
    just --list

buildTrgt := "Release"
buildTrgt_dbg := "Debug"
buildTrgt_em := "Emscripten"
buildDir := "./.build/Release"
buildDir_dbg := "./.build/Debug"
buildDir_em := "./.build/Emscripten"

# Set up development environment
bootstrap:
    git submodule deinit -f . 
    git submodule update --init --recursive
    prek install -f
    if test ! -e .venv; then \
      uv venv --python 3.13 && uv pip install -r requirements.txt && \
      uv pip install "git+https://github.com/Joecstarr/mkdocs-bibtex"; \
      uv pip install "git+https://github.com/Joecstarr/mkdocs-author-plugin"; \
    fi

test: bootstrap
    uv run pytest

html: bootstrap
    source .venv/bin/activate && \
    mkdocs build -d .site

live: bootstrap
    source .venv/bin/activate && \
    mkdocs serve --livereload

build_all : bootstrap
    if test -e {{buildDir}}; then \
        rip {{buildDir}}; \
    fi
    source .venv/bin/activate && \
    cmake -B{{buildDir}} -DCMAKE_BUILD_TYPE={{buildTrgt}} -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_COLOR_DIAGNOSTICS=TRUE -G Ninja && \
    cmake --build {{buildDir}}

test_all: bootstrap
    source .venv/bin/activate && \
    cd {{buildDir}} && \
    ctest -C {{buildTrgt}} --output-on-failure

build_em : bootstrap
    if test -e {{buildDir_dbg}}; then \
        rip {{buildDir_dbg}}; \
    fi
    source .venv/bin/activate && \
    emcmake cmake -B{{buildDir_em}} -DCMAKE_BUILD_TYPE={{buildTrgt_em}} -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_COLOR_DIAGNOSTICS=TRUE -G Ninja && \
    cmake --build {{buildDir_em}}

build_dbg : bootstrap
    if test -e {{buildDir_dbg}}; then \
        rip {{buildDir_dbg}}; \
    fi
    source .venv/bin/activate && \
    cmake -B{{buildDir_dbg}} -DCMAKE_BUILD_TYPE={{buildTrgt_dbg}} -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_COLOR_DIAGNOSTICS=TRUE -G Ninja && \
    cmake --build {{buildDir_dbg}}

test_dbg: bootstrap
    source .venv/bin/activate && \
    cd {{buildDir_dbg}} && \
    ctest -C {{buildTrgt_dbg}}

do-cmakeformat:
    find ./source/ -name 'CMakeLists.txt' -exec cmake-format -i {} \;
    cmake-format -i ./libraries/CMakeLists.txt

check-cmakeformat:
    find ./source/ -name 'CMakeLists.txt' -exec cmake-format --check {} \;
    cmake-format --check ./libraries/CMakeLists.txt
    @echo "🚀 Checked the cmake"
    exit 0

report-cppcheck:
    mkdir -p {{buildDir}}/cppcheck
    cppcheck --project={{buildDir}}/compile_commands.json -q -ilibraries/**/*  --enable=all --std=c89   --inline-suppr            --suppressions-list=cppcheck.supp --xml 2> {{buildDir}}/cppcheck/err.xml
    cppcheck-htmlreport --file={{buildDir}}/cppcheck/err.xml --report-dir={{buildDir}}/cppcheck --source-dir=.

open-cppcheck: report-cppcheck
    chromium {{buildDir}}/cppcheck/index.html

check-cppcheck:
    cppcheck --project={{buildDir}}/compile_commands.json -q -ilibraries/**/*  --enable=all  --std=c89     --inline-suppr      --error-exitcode=1       --suppressions-list=cppcheck.supp 

do-uncrustify:
    find ./source -iname "*.c"   -exec  sh -c 'uncrustify -c .uncrustify.cfg --replace "$0" || kill $PPID' \{\} \;
    find ./source -iname "*.h"   -exec  sh -c 'uncrustify -c .uncrustify.cfg --replace "$0" || kill $PPID' \{\} \;
    find ./source -iname "*.cpp" -exec  sh -c 'uncrustify -c .uncrustify.cfg --replace "$0" || kill $PPID' \{\} \;
    
check-uncrustify:
    find ./source -iname "*.c"   -exec  sh -c 'uncrustify -c .uncrustify.cfg --check "$0" || kill $PPID' \{\} \;
    find ./source -iname "*.h"   -exec  sh -c 'uncrustify -c .uncrustify.cfg --check "$0" || kill $PPID' \{\} \;
    find ./source -iname "*.cpp" -exec  sh -c 'uncrustify -c .uncrustify.cfg --check "$0" || kill $PPID' \{\} \;
    @echo "🚀 Checked the source"
    exit 0

check-mdformat: 
    source .venv/bin/activate && \
    mdformat docs --check && \
    mdformat source --check 
    @echo "🚀 Checked the Markdown"
    exit 0

do-mdformat:
    source .venv/bin/activate && \
    mdformat  docs && \
    mdformat source

check: check-mdformat check-cmakeformat check-uncrustify check-cppcheck 
    @echo "🚀 Checked the files"
    exit 0

format: do-mdformat do-cmakeformat do-uncrustify check
    @echo "🚀 Formated the files"
    exit 0