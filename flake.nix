{
  description = "Flake";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixpkgs-unstable";
  };

  outputs =
    { self, nixpkgs }:
    let
      system = "x86_64-linux";
      pkgs = nixpkgs.legacyPackages.${system};
    in
    {

      devShells.${system}.default =
        pkgs.mkShell.override
          {
            # Override stdenv in order to change compiler:
          }
          {
            buildInputs = with pkgs; [
              act
              clang-tools
              cmake
              codespell
              cppcheck
              doxygen
              heaptrack
              gcc
              gdb
              git
              git-crypt
              graphviz
              gtest
              imagemagick
              inkscape
              just
              ninja
              prettier
              openssl
              prek
              python313
              python313Packages.lizard
              rip2
              ruff
              stdenv.cc.cc.lib
              stdenv.cc.cc
              svg2pdf
              taglib
              tectonic
              uncrustify
              uv
              wget
              zip
              zlib
              cmake-format
              gsl
              bison
              flex
              mermaid-cli
              janet
            ];

            shellHook = ''
              prek install -f
              just bootstrap
              source .venv/bin/activate
              echo done!
            '';
          };
    };
}