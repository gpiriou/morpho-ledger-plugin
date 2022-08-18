import { nano_models, processTest, populateTransaction } from "../../../test.fixture";

const contractName = "Morpho";
const contractAddr = "0x8888882f8f843896699869179fb6e4f7e3b58888";
const testNetwork = "ethereum";

const testLabel = "testing_dummy"; // <= Name of the test
const testDirSuffix = testLabel.toLowerCase().replace(/\s+/g, '_');

const inputData = "0xf3fef3a300000000000000000000000039aa39c021dfbae8fac545936693ac917d5e756300000000000000000000000000000000000000000000000000000000004c4c8a";

const models = [
	{
		name: 'nanos',
		steps: 6
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