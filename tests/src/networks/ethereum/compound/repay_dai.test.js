import { nano_models, processTest, populateTransaction } from "../../../../test.fixture";

const contractName = "Morpho";
const contractAddr = "0x8888882f8f843896699869179fb6e4f7e3b58888";
const testNetwork = "ethereum";

const testLabel = "repay_dai"; // <= Name of the test
const testDirSuffix = testLabel.toLowerCase().replace(/\s+/g, '_');

// https://etherscan.io/tx/0x83d9edbf206976a776dcf3aeee0eeb6e69f29877dd065c1aea6d8587b0a33e77 // but user_address address is modified to match speculos address (5207948d16d4d78893692d369ae62888aa398f58 -> DAD77910DBDFDE764FC21FCD4E74D71BBACA6D8D).
const inputData = "0x1da649cf0000000000000000000000005d3a536e4d6dbd6114cc1ead35777bab948e3643000000000000000000000000DAD77910DBDFDE764FC21FCD4E74D71BBACA6D8D0000000000000000000000000000000000000000000074736e2a3a37bec74068";

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