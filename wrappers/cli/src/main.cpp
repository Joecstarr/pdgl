/*!
 *  \file main.cpp
 *
 *  \brief Wrapper for CLI usage of the PDGL toolchain
 *
 *
 *  \author Joe Starr
 *
 */

#include <ostream>
#include <pdgl_defs.h>
#include <production_store.h>
#include <toml_parser.h>
#include <resolution_machine.h>
#include <cxxopts.hpp>

#include <cstddef>
#include <string>
#include <iostream>
#include <random>

/**
 * \class PDGL_cli
 * \brief Wrapper class for the PDGL core library functionality
 *
 */
class PDGL_cli {
public:
    PDGL_cli(const std::string *input, size_t stack_size, size_t seed);
    explicit PDGL_cli(const std::string *input);
    ~PDGL_cli();
    bool run();

private:
    void init(const std::string *input, size_t stack_size, size_t seed);

    const std::string *language;                                         /**< Language specification
                                                                          * TOML data. */
    prodstr_store_t *store;                                              /**< Pointer to a
                                                                          * production store for the
                                                                          * language.*/
    resmach_stack_t *stack;                                              /**< A stack used for
                                                                          * storage of partial
                                                                          * resolutions. */
    size_t stack_size;                                                   /**< Size to configure the
                                                                          * stack to. */
    size_t seed;                                                         /**< Unsigned integer used
                                                                          * to seed the random
                                                                          * number generator. */
};

/**
 * \brief Deconstructor frees C library pointers.
 */
PDGL_cli::~PDGL_cli()
{
    if (nullptr != this->store)
    {
        tomlprsr_free(this->store);
    }

    for (size_t i = 0; i < this->stack_size; i++)
    {
        delete[] this->stack->partials[i].buff;
    }
    delete[] this->stack->partials;
    delete this->stack;
}

/**
 * \brief Constructor with all possible configurable items.
 *
 * \param input A pointer to a language string containing TOML data.
 * \param stack_size The size of the stack to configure.
 * \param seed The seed to use to seed random.
 */
PDGL_cli::PDGL_cli(const std::string *input, size_t stack_size, size_t seed)
{
    this->init(input, stack_size, seed);
}

/**
 * \brief constructor with minimal configurable items.
 *
 * \param input A pointer to a language string containing TOML data.
 */
PDGL_cli::PDGL_cli(const std::string *input)
{
    std::random_device rd;

    this->init(input, 100, rd());
}

/**
 * \brief Private constructor logic.
 *
 * \param input A pointer to a language string containing TOML data.
 * \param stack_size The size of the stack to configure.
 * \param seed The seed to use to seed random.
 */
void PDGL_cli::init(const std::string *input, size_t stack_size, size_t seed)
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

/**
 * \brief Run the generation of a word in the configured language.
 *
 * \return True when successful, false when failure.
 */
bool PDGL_cli::run()
{
    /* Parse the TOML */
    this->store = tomlprsr_parse(static_cast <const char *>(this->language->c_str()));
    if (nullptr != this->store)
    {
        srand(this->seed);

        /* Run the machine */
        unsigned int ret_val = resmach_execute(this->store, this->stack, stdout);

        if (ret_val != RESMACH_EXECUTE_SUCCESS)
        {
            /* When error happens, diagnose it and report. */
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

/**
 * \brief Main calling routine.
 *
 * \param argc A count of arguments.
 * \param argv A list of void pointers to argument.
 * \return An exit code 0 indicating success or failure otherwise.
 */
int main(int argc, char **argv)
{
    cxxopts::Options options("test", "A brief description");

    options.add_options()
    ("c,count", "Number of words to produce", cxxopts::value <size_t> ()->default_value("10"))
    ("s,stack", "Size of stack to use", cxxopts::value <size_t> ()->default_value("100"))
    ("h,help", "Print usage")
    ;

    auto result = options.parse(argc, argv);

    if (result.count("help"))
    {
        std::cout << options.help() << std::endl;
        exit(0);
    }

    size_t count      = result["count"].as <size_t>();
    size_t stack_size = result["stack"].as <size_t>();

    std::random_device rd;
    std::string        language;

    /*@@@NOTE: I'm not sure if this is really a great way to do this. It requires feeding of an EOF
     * symbol. */
    do{
        std::string temp;
        std::getline(std::cin, temp);
        language += temp + "\n";
    }while (!std::cin.eof());

    for (size_t i = 0; i < count; i++)
    {
        PDGL_cli *pdgl    = new PDGL_cli(&language, stack_size, rd());
        bool      success = pdgl->run();
        delete pdgl;
        if (!success)
        {
            return 1;
        }
    }

    return 0;
}
