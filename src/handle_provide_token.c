#include "morpho_plugin.h"

void handle_provide_token(void *parameters)
{
    PRINTF("GPIRIOU PROVIDE TOKEN\n");
    ethPluginProvideInfo_t *msg = (ethPluginProvideInfo_t *)parameters;

    msg->result = ETH_PLUGIN_RESULT_OK;
}