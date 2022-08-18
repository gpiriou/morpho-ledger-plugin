import { nano_models, processTest, populateTransaction } from "../../../test.fixture";

const contractName = "Morpho";
const contractAddr = "0x8888882f8f843896699869179fb6e4f7e3b58888";
const testNetwork = "ethereum";

const testLabel = "borrow_weth"; // <= Name of the test
const testDirSuffix = testLabel.toLowerCase().replace(/\s+/g, '_');

// https://etherscan.io/tx/0xd947499c02fd690227cbf833107a320cd8f58e16c795b3dd023f7ac6eb957e64
const inputData = "0x4b8a35290000000000000000000000004ddc2d193948926d02f9b1fe9e1daa0718270ed500000000000000000000000000000000000000000000003635c9adc5dea00000";

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