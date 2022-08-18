#include "morpho_plugin.h"

void handle_provide_token(void *parameters)
{
    PRINTF("GPIRIOU PROVIDE TOKEN\n");
    ethPluginProvideInfo_t *msg = (ethPluginProvideInfo_t *)parameters;
    // context_t *context = (context_t *)msg->pluginContext;

    // The Ethereum App found the information for the requested token!
    //if (msg->item1)
    //{
    //    // Store its decimals.
    //    context->token_decimals = msg->item1->token.decimals;
    //    // Store its ticker.
    //    strlcpy(context->token_ticker, (char *)msg->item1->token.ticker, sizeof(context->token_ticker));
    //}
    //else
    //    PRINTF("handle_provide_token NO item1\n");

    msg->result = ETH_PLUGIN_RESULT_OK;
}