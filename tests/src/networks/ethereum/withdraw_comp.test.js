import { nano_models, processTest, populateTransaction } from "../../../test.fixture";

const contractName = "Morpho";
const contractAddr = "0x8888882f8f843896699869179fb6e4f7e3b58888";
const testNetwork = "ethereum";

const testLabel = "withdraw_comp"; // <= Name of the test
const testDirSuffix = testLabel.toLowerCase().replace(/\s+/g, '_');

// https://etherscan.io/tx/0xa71b6c046374806bf154d13f82e1f39df25b0d0a9e4183ad8217c8288ea6fefa
const inputData = "0xf3fef3a300000000000000000000000070e36f6bf80a52b3b46b3af8e106cc0ed743e8e4000000000000000000000000000000000000000000000fac3e3d2043484f0000";

const models = [
	{
		name: 'nanos',
		steps: 4
	},
	//{
	//	name: 'nanox',
	//	steps: 6
	//},
]

// populate unsignedTx from genericTx and get network chain id
const unsignedTx = populateTransaction(contractAddr, inputData, testNetwork);
// Process tests for each nano models
models.forEach((model) => {
	const nano_model = nano_models.find((nano_model) => nano_model.name === model.name)
	processTest(nano_model, model.steps, contractName, testLabel, testDirSuffix, unsignedTx, testNetwork)
})