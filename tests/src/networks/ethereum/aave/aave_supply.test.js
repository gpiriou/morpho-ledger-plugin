import { nano_models, processTest, populateTransaction } from "../../../../test.fixture";

const contractName = "Morpho";
const contractAddr = "0x777777c9898d384f785ee44acfe945efdff5f3e0";
const testNetwork = "ethereum";

const testLabel = "aave_supply"; // <= Name of the test
const testDirSuffix = testLabel.toLowerCase().replace(/\s+/g, '_');

// https://etherscan.io/tx/0x21493c2c08bd93abd576a0661647991228748779c584b84644b5585067bba8e5 // but user_address address is modified to match speculos address (6e632701fd42a9b856294a2172dd63f03eb957c5 -> DAD77910DBDFDE764FC21FCD4E74D71BBACA6D8D).
const inputData = "0x0c0a769b0000000000000000000000001982b2f5814301d4e9a8b0201555376e62f82428000000000000000000000000DAD77910DBDFDE764FC21FCD4E74D71BBACA6D8D000000000000000000000000000000000000000000000000016345785d8a0000";

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