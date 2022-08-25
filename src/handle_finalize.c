#include "morpho_plugin.h"

void handle_finalize(void *parameters)
{
    ethPluginFinalize_t *msg = (ethPluginFinalize_t *)parameters;
    context_t *context = (context_t *)msg->pluginContext;

    // set default numScreens

    PRINTF("GPIRIOU FINALIZE\n");
    msg->numScreens = 1;

    if (context->selectorIndex == SUPPLY || context->selectorIndex == REPAY || context->selectorIndex == CLAIM)
    {
        if (memcmp(context->user_address, msg->address, ADDRESS_LENGTH))
        {
            PRINTF("MSG PARAMETER: %.*H\n",
                   ADDRESS_LENGTH,
                   context->user_address);
            PRINTF("MSG ADDRESS: %.*H\n",
                   ADDRESS_LENGTH,
                   msg->address);
            context->user_warning = 1;
            msg->numScreens++;
        }
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