/**
 *  \file prod_janet.c
 *
 *  \brief Defines the functionality of a Janet production, allowing for injection of arbitrary
 *Janet code.
 *
 *
 *  \author Joe Starr
 *
 */

#include "prod_janet.h"
#include <string.h>
#include <pdgl_defs.h>
#include <janet.h>
#include <fmem.h>
#include <stdbool.h>

/*************************************************************************************************/
/************************** Extern ***************************************************************/
/*************************************************************************************************/

/**
 * \brief An external reference to a build time created byte array of `./init_script.janet`.
 */
extern const unsigned char init_script_janet[];

/*************************************************************************************************/
/************************** Defines **************************************************************/
/*************************************************************************************************/

/*************************************************************************************************/
/************************** Typedefs *************************************************************/
/*************************************************************************************************/

/*************************************************************************************************/
/************************** Private Function Declarations ****************************************/
/*************************************************************************************************/
STATIC_INLINE char *prod_janet_execute(const void *config, const char *script);

/* cppcheck-suppress constParameterCallback*/
STATIC_INLINE Janet prod_janet_pdglcout(int32_t argc, Janet *argv);


/*************************************************************************************************/
/************************** Local Variables ******************************************************/
/*************************************************************************************************/


/**
 * \brief A collection of c functions to pass to the Janet environment at init.
 */
static const JanetReg cfuns[] = {
    { "out", prod_janet_pdglcout, "Print function that pushes data onto the output string." },
    { NULL,  NULL,                NULL                                                      }
};



/*************************************************************************************************/
/************************** Public Function Definitions ******************************************/
/*************************************************************************************************/
/* Docstring in header */
const char * prod_janet_resolve(const void *config)
{
    const char *retval = NULL;

    if (NULL != config)
    {
        const prod_janet_config_t *typed_cfg = (const prod_janet_config_t *)config;
        if ((0 != typed_cfg->out_str_len) && (NULL != typed_cfg->out_str))
        {
            typed_cfg->out_str[0] = '\0';
            if (NULL != typed_cfg->repl_str)
            {
                retval = prod_janet_execute(config, typed_cfg->repl_str);
            }
        }
    }

    return retval;
}

/* Docstring in header */
const char * prod_janet_terminate(const void *config)
{
    const char *retval = NULL;

    if (NULL != config)
    {
        const prod_janet_config_t *typed_cfg = (const prod_janet_config_t *)config;
        if ((0 != typed_cfg->out_str_len) && (NULL != typed_cfg->out_str))
        {
            typed_cfg->out_str[0] = '\0';
            if (NULL != typed_cfg->term_str)
            {
                retval = prod_janet_execute(config, typed_cfg->term_str);
            }
        }
    }

    return retval;
}

/*************************************************************************************************/
/************************** Private Function Definitions *****************************************/
/*************************************************************************************************/

/**
 * \brief Execute a production in a Janet VM
 *
 * Create a Janet VM with an overloaded print statement. Pass the current production script to the
 *Janet VM and run the script.
 *
 * \param config The current production configuration. Must be cast to the Janet type.
 * \param script The script to execute one of replacement or terminal.
 * \return A pointer to the output string. NULL on error.
 */
static char * prod_janet_execute(const void *config, const char *script)
{
    {
        const prod_janet_config_t *typed_cfg = (const prod_janet_config_t *)config;
        const char * script_str = (const char *)init_script_janet;
        char *       retval     = NULL;
        JanetTable * env        = NULL;
        JanetTable * sub_env    = NULL;
        JanetBuffer *errBuffer  = NULL;
        Janet        module_cache;
        Janet        result;

        /* Initialize the virtual machine. Do this before any calls to Janet functions. */
        janet_init();

        env     = janet_core_env(NULL);
        sub_env = janet_table(0);

        /* Build new c module with print out function overloaded*/
        janet_cfuns(sub_env, "pdglc", cfuns);
        janet_def(sub_env, "cfg_ptr", janet_wrap_pointer((void *)config),
                  "Pointer to the configuration being worked on.");
        module_cache = janet_resolve_core("module/cache");
        janet_table_put(janet_unwrap_table(module_cache), janet_cstringv("pdglc"),
                        janet_wrap_table(sub_env));

        /* Replace the standard error of the Janet environment with a c string. */
        errBuffer = janet_buffer(DEFS_PDGL_MAX_STRING_SIZE);
        janet_setdyn("err", janet_wrap_buffer(errBuffer));


        /* Run the startup script to overload the print function*/

        /*@@@NOTE: I have no idea if this is a good way to do this. It seems to work and should be
         * invisible to a user. Submit a bug if there's an issue.*/

        if (0 == janet_dostring(env, script_str, "main",
                                &result))
        {
            /* Make sure the result isn't garbage collected*/
            janet_gcroot(result);
            if (0 == janet_dostring(env, script, "main", &result))
            {
                retval = typed_cfg->out_str;
            }
        }
        /* Something went wrong since `retval` is still NULL. Report that error.*/
        if (NULL == retval)
        {
            janet_stacktrace(janet_current_fiber(), result);
            janet_buffer_push_u8(errBuffer, 0);
            /*@@@TODO: Add logging fprintf(stderr, "%s", errBuffer->data); */
        }

        /* Make sure the result is garbage collected*/
        janet_gcunroot(result);

        /* Clean up the Janet VM*/
        janet_deinit();

        return retval;
    }
}

/**
 * \brief Parse a print calling back from Janet to c.
 *
 * From inside a Janet VM call back into the PDGL c code. Add the first argument to the output
 *string buffer of the config pointed to by the second argument.
 *
 * \param argc A count of arguments.
 * \param argv A list of void pointers to argument.
 * \return Pass back to the Janet VM a nil value.
 */
/* cppcheck-suppress constParameterCallback*/
STATIC_INLINE Janet prod_janet_pdglcout(int32_t argc, Janet *argv)
{
    const char *text = NULL;
    const prod_janet_config_t *typed_cfg = NULL;
    size_t cur_out_len = 0;

    /* Ensure exactly two arguments*/
    janet_fixarity(argc, 2);
    /* Parse the first argument into a string*/
    text = janet_getcstring(argv, 0);
    /* Parse the second argument into a prod_janet_config_t pointer*/
    typed_cfg   = (const prod_janet_config_t *)janet_getpointer(argv, 1);
    cur_out_len = strlen(typed_cfg->out_str);

    /* If there is room left in the output buffer for the production. */
    if (0 < cur_out_len - (strlen(typed_cfg->out_str) + strlen(text)))
    {
        char *end = typed_cfg->out_str + cur_out_len;
        sprintf(end, "%s", text);
    }
    else/* Otherwise, panic. */
    {
        janet_panicf("Buffer is out of space!");
    }

    return janet_wrap_nil();
}
