/*!
 *  @file main.cpp
 *
 *  @brief Wrapper for browser (WASM) usage of the PDGL toolchain
 *
 *
 *  @author    Joe Starr
 *
 */
#include <cstddef>
#include <cstdint>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <pdgl_defs.h>
#include <production_store.h>
#include <toml_parser.h>
#include <resolution_machine.h>
#include <iostream>
#include <random>

#ifdef ENABLE_EMSCRIPTEN
#include <emscripten.h>
#include <emscripten/bind.h>
using namespace emscripten;
#endif

class PDGL_wasm {
public:
/* cppcheck-suppress passedByValue */
    PDGL_wasm(std::string input, size_t stack_size, size_t seed);
/* cppcheck-suppress passedByValue */
    explicit PDGL_wasm(std::string input);
    ~PDGL_wasm();
    bool run();

private:
/* cppcheck-suppress passedByValue */
    void init(std::string input, size_t stack_size, size_t seed);

    std::string language;
    prodstr_store_t *store;
    resmach_stack_t *stack;
    size_t stack_size;
    size_t seed;
};

PDGL_wasm::~PDGL_wasm()
{
    for (size_t i = 0; i < this->stack_size; i++)
    {
        delete this->stack->partials[i].buff;
    }
    if (nullptr != this->store)
    {
        tomlprsr_free(this->store);
    }
    delete[] this->stack->partials;
    delete this->stack;
}

/* cppcheck-suppress passedByValue */
PDGL_wasm::PDGL_wasm(std::string input, size_t stack_size, size_t seed)
{
    this->init(input, stack_size, seed);
}

/* cppcheck-suppress passedByValue */
PDGL_wasm::PDGL_wasm(std::string input)
{
    std::random_device rd;

    this->init(input, 100, rd());
}

/* cppcheck-suppress passedByValue */
void PDGL_wasm::init(std::string input, size_t stack_size, size_t seed)
{
    this->seed             = seed;
    this->language         = input;
    this->store            = nullptr;
    this->stack_size       = stack_size;
    this->stack            = new resmach_stack_t{ nullptr };
    this->stack->stack_len = this->stack_size;
    this->stack->partials  = new resmach_partial_t[this->stack_size];
    for (size_t i = 0; i < this->stack_size; i++)
    {
        this->stack->partials[i].partial_ptr = new char[DEFS_PDGL_MAX_STRING_SIZE];
        this->stack->partials[i].buff        =
            static_cast <const char *>(this->stack->partials[i].partial_ptr);
    }
}

bool PDGL_wasm::run()
{
    this->store = tomlprsr_parse(static_cast <const char *>(this->language.c_str()));
    if (nullptr != this->store)
    {
        srand(this->seed);

        unsigned int ret_val = resmach_execute(this->store, this->stack, stdout);

        if (ret_val != RESMACH_EXECUTE_SUCCESS)
        {
            std::string error_rpt = "";
            if ((ret_val & RESMACH_EXECUTE_NO_ENTRY) == RESMACH_EXECUTE_NO_ENTRY)
            {
                error_rpt += "* No entry production in toml\n";
            }
            std::cout << "Error in execution! Found the following:" << std::endl << error_rpt
                      << std::endl;
            return false;
        }
    }
    else
    {
        std::cout
            <<
            "Error in Parsing the toml! Check your toml syntax and check you have an entry production."
            << std::endl;
        return false;
    }
    std::cout << std::endl;
    return true;
}

#ifdef ENABLE_EMSCRIPTEN
EMSCRIPTEN_BINDINGS(notewptt)
{
    /*  clang-format off  */
    class_<PDGL_wasm>("PDGL")
           .constructor<std::string>()
           .constructor<std::string,size_t,size_t>()
           .function("run", &PDGL_wasm::run);
    /* clang-format on */
}
#else

int main()
{
    std::random_device rd;

    /*  clang-format off  */
    std::string str =  "[[production]] \n\
                        name = \"entry\" \n\
                        type = \"pure\" \n\
                        transitions = [\"%{a}\"] \n\
                        terminals = [\"\"] \n\
                        \n\
                        [[production]] \n\
                        name = \"a\" \n\
                        type = \"pure\" \n\
                        transitions = [\"(%{a})\", \"%{a}%{a}\", \"\"] \n\
                        terminals = [\"\"]";
    /* clang-format on */
    for (size_t i = 0; i < 10; i++)
    {
        PDGL_wasm *pdgl    = new PDGL_wasm(str, 100, rd());
        bool       success = pdgl->run();
        delete pdgl;
        if (!success)
        {
            return 1;
        }
    }


    return 0;
}

#endif
