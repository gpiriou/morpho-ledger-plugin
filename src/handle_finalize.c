#include "morpho_plugin.h"

void handle_finalize(void *parameters)
{
    ethPluginFinalize_t *msg = (ethPluginFinalize_t *)parameters;
    context_t *context = (context_t *)msg->pluginContext;

    // set default numScreens
    msg->numScreens = 1;

    switch (context->selectorIndex)
    {
    case COMPOUND_SUPPLY:
    case COMPOUND_REPAY:
    case AAVE_SUPPLY:
    case AAVE_REPAY:
    case COMMON_CLAIM:
        if (memcmp(context->user_address, msg->address, ADDRESS_LENGTH))
        {
            PRINTF("USER WARNING RAISED\n");
            PRINTF("PARAMETER: %.*H\n",
                   ADDRESS_LENGTH,
                   context->user_address);
            PRINTF("USER ADDRESS: %.*H\n",
                   ADDRESS_LENGTH,
                   msg->address);
            context->on_behalf = 1;
            msg->numScreens++;
        }
        break;
    default:
        break;
    }
    if (context->token_warning)
        msg->numScreens++;

    PRINTF("Setting tokenLookup1 to: %.*H\n",
           ADDRESS_LENGTH,
           context->pool_token_address);
    msg->tokenLookup1 = context->pool_token_address;

    msg->uiType = ETH_UI_TYPE_GENERIC;
    msg->result = ETH_PLUGIN_RESULT_OK;
}