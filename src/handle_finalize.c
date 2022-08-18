#include "morpho_plugin.h"

void handle_finalize(void *parameters)
{
    ethPluginFinalize_t *msg = (ethPluginFinalize_t *)parameters;
    context_t *context = (context_t *)msg->pluginContext;

    // set default numScreens

    PRINTF("GPIRIOU FINALIZE\n");
    msg->numScreens = 1;

    if (context->selectorIndex == SUPPLY || context->selectorIndex == REPAY)
    {
        if (memcmp(context->on_behalf, msg->address, ADDRESS_LENGTH))
        {
            PRINTF("ON BEHALF: %.*H\n",
                   ADDRESS_LENGTH,
                   context->on_behalf);
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