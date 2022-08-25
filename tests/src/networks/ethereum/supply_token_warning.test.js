import { nano_models, processTest, populateTransaction } from "../../../test.fixture";

const contractName = "Morpho";
const contractAddr = "0x8888882f8f843896699869179fb6e4f7e3b58888";
const testNetwork = "ethereum";

const testLabel = "supply_token_warning"; // <= Name of the test
const testDirSuffix = testLabel.toLowerCase().replace(/\s+/g, '_');

// https://etherscan.io/tx/0x059909b8b2e1ed385cfdeb2812429abd93e4965af7ac57bd754adf3d4bc99e40 but user_address address is modified to match speculos address (dd2b3f1d3a4f08622a25a3f75284fc01ad0c5cca -> DAD77910DBDFDE764FC21FCD4E74D71BBACA6D8D). 
// and cUSDC address modified to raise token warning (39aa3 -> 39aa4)
const inputData = "0x0c0a769b00000000000000000000000039aa49c021dfbae8fac545936693ac917d5e7563000000000000000000000000DAD77910DBDFDE764FC21FCD4E74D71BBACA6D8D00000000000000000000000000000000000000000000000000000000004c4b40";

const models = [
	{
		name: 'nanos',
		steps: 5
	},
	// {
	// 	name: 'nanox',
	// 	steps: 5
	// },
]

// populate unsignedTx from genericTx and get network chain id
const unsignedTx = populateTransaction(contractAddr, inputData, testNetwork);
// Process tests for each nano models
models.forEach((model) => {
	const nano_model = nano_models.find((nano_model) => nano_model.name === model.name)
	processTest(nano_model, model.steps, contractName, testLabel, testDirSuffix, unsignedTx, testNetwork)
})