import { nano_models, processTest, populateTransaction } from "../../../../test.fixture";

const contractName = "RewardsDistributor";
const contractAddr = "0x3b14e5c73e0a56d607a8688098326fd4b4292135";
const testNetwork = "ethereum";

const testLabel = "common_claim"; // <= Name of the test
const testDirSuffix = testLabel.toLowerCase().replace(/\s+/g, '_');

// https://etherscan.io/tx/0x871ae4c38e58f9ea12f37d42f5a52d34b7503429a8616263bb64d4c2306a98dc // but user_address address is modified to match speculos address (dd2b3f1d3a4f08622a25a3f75284fc01ad0c5cca -> DAD77910DBDFDE764FC21FCD4E74D71BBACA6D8D).
const inputData = "0x3d13f874000000000000000000000000DAD77910DBDFDE764FC21FCD4E74D71BBACA6D8D00000000000000000000000000000000000000000000000000062aeaa5bb4ef50000000000000000000000000000000000000000000000000000000000000060000000000000000000000000000000000000000000000000000000000000000aa9ef09d4d926f15af138432fca248caa89ddbb1e6c452f8957445f85f57fcdec3164e7f3cccc75f0410b30b0345d873490a2b829a35e100f4cfc7a19b0b3a37ae0b593ac2e7f9a465d745bc7483d37cbbd939b375b49cb6597e2ae1eddcd04d73a404cf2acf727774e3ff5fa5e381249d8bbe23fbe1fe92716e56edc81243cb9ee1f2b76467e530d4cc383a679bf356f0773e2718476a53e240c885146a94a2c13df8e4b877eec8c4a845cd68a26f4e04311dd1f6469b82d474392cd66ca63fbf90bd48aa7151146d09642903a830b7db38e62abd802fc67e41fa9d6c77134eb493ef096c0a27985160d0a5dc07948cf6d4cdef5f4f20b75cb8cce0ca7ab5fb5ee358e36e5e5614451490385eeaee720f0b2dfd11c046b9bfe8742f6ea2e16e6de33d37b94a17c60ab9e442c1921184bec0a7e3fb0153df8aa6eb5204b34adb2";

const models = [
  {
    name: 'nanos',
    steps: 4
  },
  {
    name: 'nanox',
    steps: 4
  },
  {
    name: 'nanosp',
    steps: 4
  },
]

// populate unsignedTx from genericTx and get network chain id
const unsignedTx = populateTransaction(contractAddr, inputData, testNetwork);
// Process tests for each nano models
models.forEach((model) => {
  const nano_model = nano_models.find((nano_model) => nano_model.name === model.name)
  processTest(nano_model, model.steps, contractName, testLabel, testDirSuffix, unsignedTx, testNetwork)
})
