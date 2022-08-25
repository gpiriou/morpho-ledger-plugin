#include "morpho_plugin.h"
#include "text.h"

// Sets the first screen to display.
void handle_query_contract_id(void *parameters)
{
    ethQueryContractID_t *msg = (ethQueryContractID_t *)parameters;
    // msg->name will be the upper sentence displayed on the screen.
    // msg->version will be the lower sentence displayed on the screen.

    uint8_t COMPOUND_MORPHO_CONTRACT[ADDRESS_LENGTH] = {0x88, 0x88, 0x88, 0x2F, 0x8F, 0x84, 0x38, 0x96, 0x69, 0x98, 0x69, 0x17, 0x9F, 0xB6, 0xE4, 0xF7, 0xE3, 0xB5, 0x88, 0x88};
    // uint8_t AAVE_MORPHO_CONTRACT[ADDRESS_LENGTH] = {};

    // For the first screen, display the plugin name.
    strlcpy(msg->name, PLUGIN_NAME, msg->nameLength);

    if (!(memcmp(COMPOUND_MORPHO_CONTRACT, msg->pluginSharedRO->txContent->destination, ADDRESS_LENGTH)))
        strlcpy(msg->version, MSG_COMPOUND_ID, msg->versionLength);
    //else if (!(memcmp(AAVE_MORPHO_CONTRACT, msg->pluginSharedRO->txContent->destination, ADDRESS_LENGTH))
    //    strlcpy(msg->version, MSG_AAVE_ID, msg->versionLength);
    else
    {
        msg->result = ETH_PLUGIN_RESULT_ERROR;
        return;
    }
    msg->result = ETH_PLUGIN_RESULT_OK;
}