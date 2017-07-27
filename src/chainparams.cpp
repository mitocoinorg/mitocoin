// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "consensus/merkle.h"

#include "tinyformat.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

#include "chainparamsseeds.h"

#include <iostream>   // std::cout
#include <string>

#include "util.h"
using namespace std;



static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;

    CBlock genesis;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(txNew);
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;
}

/**
 * Build the genesis block. Note that the output of its generation
 * transaction cannot be spent since it did not originally exist in the
 * database.
 *
 * CBlock(hash=000000000019d6, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=4a5e1e, nTime=1231006505, nBits=1d00ffff, nNonce=2083236893, vtx=1)
 *   CTransaction(hash=4a5e1e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
 *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d0104455468652054696d65732030332f4a616e2f32303039204368616e63656c6c6f72206f6e206272696e6b206f66207365636f6e64206261696c6f757420666f722062616e6b73)
 *     CTxOut(nValue=50.00000000, scriptPubKey=0x5F1DF16B2B704C8A578D0B)
 *   vMerkleTree: 4a5e1e
 */
static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "A moeda brasileira, a moeda dos mitos";
    const CScript genesisOutputScript = CScript() << ParseHex("040184710fa689ad5023690c80f3a49c8f13f8d45b8c857fbcbc8bc4a8e4d3eb4b10f4d4604fa08dce601aaf0f470216fe1b51850b4acf21b179c45070ac7b03a9") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

/**
 * Main network
 */
/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *   (no blocks before with a timestamp after, none after with
 *    timestamp before)
 * + Contains no strange transactions
 */
// std::string CBlockFileInfo::ToString() const {
//      return strprintf("CBlockFileInfo(blocks=%u, size=%u, heights=%u...%u, time=%s...%s)", nBlocks, nSize, nHeightFirst, nHeightLast, DateTimeStrFormat("%Y-%m-%d", nTimeFirst), DateTimeStrFormat("%Y-%m-%d", nTimeLast));
//  }

class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = "main";
        consensus.nSubsidyHalvingInterval = 1000000;
        consensus.nMajorityEnforceBlockUpgrade = 750;
        consensus.nMajorityRejectBlockOutdated = 950;
        consensus.nMajorityWindow = 1000;
        consensus.BIP34Height = 710000;
        consensus.BIP34Hash = uint256S("fa09d204a83a768ed5a7c8d441fa62f2043abf420cff1226c7b4329aeb9d51cf");
        consensus.powLimit = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"); 
        consensus.nPowTargetTimespan = 2 * 24 * 60 * 60; // 1 days
        consensus.nPowTargetSpacing = 2 * 60;
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 4320; // 75% of 5760
        consensus.nMinerConfirmationWindow = 5760; // nPowTargetTimespan / nPowTargetSpacing * 4
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1497958610; // , 2017
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1517356801; // January 31st, 2018

        // Deployment of SegWit (BIP141, BIP143, and BIP147)
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 1497958610; // , 2017
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 1517356801; // January 31st, 2018

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x000000000000000000000000000000000000000000000005c13f99f6d0b1a908");
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 32-bit integer with any alignment.
         */
        pchMessageStart[0] = 0xbb;
        pchMessageStart[1] = 0xc3;
        pchMessageStart[2] = 0xd6;
        pchMessageStart[3] = 0xeb;
        nDefaultPort = 59333;//from 59333 to 
        nPruneAfterHeight = 100000;

        genesis = CreateGenesisBlock(1501108258, 1423337, 0x1e0ffff0, 1, 50 * COIN);

        // consensus.hashGenesisBlock = uint256S("0x0000000000000000000000000000000000000000000000000000000000000001");
        
            // cout << "old pow" + genesis.GetPoWHash().ToString() << endl;
        

        // if (true && genesis.GetHash() != consensus.hashGenesisBlock)
        // {
        //     cout << "entraa" << endl;

        //     LogPrintf("recalculating params for mainnet.\n");
        //     LogPrintf("old mainnet genesis nonce: %s\n", std::to_string(genesis.nNonce));
        //     // strprintf(consensus.hashGenesisBlock);
        //     LogPrintf("old mainnet genesis hash:  %s\n", consensus.hashGenesisBlock.ToString());
        //     cout << "old " + genesis.GetHash().ToString() << endl;

        //     // deliberately empty for loop finds nonce value.
        //     for(genesis.nNonce = 0; consensus.powLimit < genesis.GetPoWHash()  ; genesis.nNonce++){ 
        //         cout << std::to_string(genesis.nNonce) << endl;
        //         cout << genesis.GetHash().ToString() << endl;
        //     } 
        //     cout << "new pow " + genesis.GetPoWHash().ToString() << endl;

        //     LogPrintf("new mainnet genesis merkle root: %s\n", genesis.hashMerkleRoot.ToString());
        //     LogPrintf("new mainnet genesis nonce: %s\n", genesis.nNonce);
        //     LogPrintf("new mainnet genesis hash: %s\n", genesis.GetHash().ToString());
        // }

        

        consensus.hashGenesisBlock = genesis.GetHash();
        // cout << consensus.hashGenesisBlock.ToString() << endl;
        // cout << std::to_string(genesis.nNonce) << endl;
        // cout << std::to_string(genesis.nNonce) << endl;
        // cout << genesis.hashMerkleRoot.ToString()<< endl;
                //fc540599a3265e4526f331cda4c32fac8c35018ea394e913cfcf74bc16808e8c
        //0x6a33cc213ec3f1b1126ba37b9933d44af40c570ae0c4a623b7d3c1959b3646c2
        assert(consensus.hashGenesisBlock == uint256S("0xb00d430b50159efe556bf075d2c5011ecfaa5aa9d5f37b53cdb16bb078d618f6"));
        assert(genesis.hashMerkleRoot == uint256S("0x72f9d3391b971575a87e1cf679170eef7497f94b8e4999b2e1e6fe38f036bf61"));

        // Note that of those with the service bits flag, most only support a subset of possible options
        vFixedSeeds.clear();
        vSeeds.clear();
        // vSeeds.push_back(CDNSSeedData("loshan.co.uk", "seed-a.mitocoin.loshan.co.uk", true));
        // vSeeds.push_back(CDNSSeedData("thrasher.io", "dnsseed.thrasher.io", true));
        // vSeeds.push_back(CDNSSeedData("mitocointools.com", "dnsseed.mitocointools.com"));
        // vSeeds.push_back(CDNSSeedData("mitocoinpool.org", "dnsseed.mitocoinpool.org"));
        // vSeeds.push_back(CDNSSeedData("koin-project.com", "dnsseed.koin-project.com"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,38);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,5);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,176);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = false;

	checkpointData = (CCheckpointData) {
		boost::assign::map_list_of
			(  0, uint256S("0xb00d430b50159efe556bf075d2c5011ecfaa5aa9d5f37b53cdb16bb078d618f6"))
			,
			1501108258, // * UNIX timestamp of last checkpoint block
			0,   // * total number of transactions between genesis and last checkpoint
			//   (the tx=... number in the SetBestChain debug.log lines)
			500.0     // * estimated number of transactions per day after checkpoint
	};

    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CChainParams {
public:
    CTestNetParams() {
        strNetworkID = "test";
        consensus.nSubsidyHalvingInterval = 1000000;
        consensus.nMajorityEnforceBlockUpgrade = 51;
        consensus.nMajorityRejectBlockOutdated = 75;
        consensus.nMajorityWindow = 100;
        consensus.BIP34Height = 400000;
        consensus.BIP34Hash = uint256S("0x860157ab24717e9694216938a9ae08cf4d58a15ca59a861e2d8469af0e6a1d50");
        consensus.powLimit = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 2 * 24 * 60 * 60; // 1 days
        consensus.nPowTargetSpacing = 2 * 60;
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 1512; // 75% for testchains
        consensus.nMinerConfirmationWindow = 1440; // nPowTargetTimespan / nPowTargetSpacing
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1485561600; // January 1, 2017
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1517356801; // January 31st, 2018

        // Deployment of SegWit (BIP141, BIP143, and BIP147)
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 1485561600; // January 1, 2017
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 1517356801; // January 31st, 2018

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00000000000000000000000000000000000000000000000000006fce5d67766e");

        pchMessageStart[0] = 0xac;
        pchMessageStart[1] = 0xe1;
        pchMessageStart[2] = 0xd4;
        pchMessageStart[3] = 0xdf;
        nDefaultPort = 159333;//from 159333 to 
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1491108861, 1121377, 0x1e0ffff0, 1, 50 * COIN);
        // added by freeman
        //consensus.hashGenesisBlock = uint256S("0x0000000000000000000000000000000000000000000000000000000000000001");
        if (false && genesis.GetHash() != consensus.hashGenesisBlock)
        {
            LogPrintf("recalculating params for testnet.\n");
            LogPrintf("old mainnet genesis nonce: %s\n", std::to_string(genesis.nNonce));
            LogPrintf("old mainnet genesis hash:  %s\n", consensus.hashGenesisBlock.ToString());
            // deliberately empty for loop finds nonce value.
            for(genesis.nNonce = 0; consensus.powLimit < genesis.GetHash(); genesis.nNonce++){ } 
            LogPrintf("new mainnet genesis merkle root: %s\n", genesis.hashMerkleRoot.ToString());
            LogPrintf("new mainnet genesis nonce: %s\n", std::to_string(genesis.nNonce));
            LogPrintf("new mainnet genesis hash: %s\n", genesis.GetHash().ToString());
        }
        consensus.hashGenesisBlock = genesis.GetHash();
        // cout << consensus.hashGenesisBlock.ToString() << endl;
        // cout << genesis.hashMerkleRoot.ToString() << endl;
        assert(consensus.hashGenesisBlock == uint256S("0xe832f185135133f0ee95a778e531e564a531b20cd4da69a756d4f14b64c3e531"));
        assert(genesis.hashMerkleRoot == uint256S("0x72f9d3391b971575a87e1cf679170eef7497f94b8e4999b2e1e6fe38f036bf61"));

        vFixedSeeds.clear();
        vSeeds.clear();
        // nodes with support for servicebits filtering should be at the top
        vFixedSeeds.clear();
        vSeeds.clear();
        // vSeeds.push_back(CDNSSeedData("mitocointools.com", "testnet-seed.mitocointools.com"));
        // vSeeds.push_back(CDNSSeedData("loshan.co.uk", "seed-b.mitocoin.loshan.co.uk", true));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,100);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;


        checkpointData = (CCheckpointData) {
            boost::assign::map_list_of
            ( 0, uint256S("0xe832f185135133f0ee95a778e531e564a531b20cd4da69a756d4f14b64c3e531")),
            1491108861,
            0,
            200            
        };

    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CChainParams {
public:
    CRegTestParams() {
        strNetworkID = "regtest";
        consensus.nSubsidyHalvingInterval = 150;
        consensus.nMajorityEnforceBlockUpgrade = 750;
        consensus.nMajorityRejectBlockOutdated = 950;
        consensus.nMajorityWindow = 1000;
        consensus.BIP34Height = -1; // BIP34 has not necessarily activated on regtest
        consensus.BIP34Hash = uint256();
        consensus.powLimit = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 3.5 * 24 * 60 * 60; // two weeks
        consensus.nPowTargetSpacing = 2.5 * 60;
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = true;
        consensus.nRuleChangeActivationThreshold = 108; // 75% for testchains
        consensus.nMinerConfirmationWindow = 144; // Faster than normal for regtest (144 instead of 2016)
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 999999999999ULL;

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00");

        pchMessageStart[0] = 0xfb;
        pchMessageStart[1] = 0xbd;
        pchMessageStart[2] = 0xb1;
        pchMessageStart[3] = 0xdc;
        nDefaultPort = 19444;
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1481109615, 1053647, 0x1e0ffff0, 1, 50 * COIN);

        //consensus.hashGenesisBlock = uint256S("0x0000000000000000000000000000000000000000000000000000000000000001");
        if (false && genesis.GetHash() != consensus.hashGenesisBlock)
        {
            LogPrintf("recalculating params for regtest.\n");
            LogPrintf("old mainnet genesis nonce: %s\n", std::to_string(genesis.nNonce));
            LogPrintf("old mainnet genesis hash:  %s\n", consensus.hashGenesisBlock.ToString());
            // deliberately empty for loop finds nonce value.
            for(genesis.nNonce = 0; consensus.powLimit < genesis.GetHash(); genesis.nNonce++){ } 
            LogPrintf("new mainnet genesis merkle root: %s\n", genesis.hashMerkleRoot.ToString());
            LogPrintf("new mainnet genesis nonce: %s\n", std::to_string(genesis.nNonce));
            LogPrintf("new mainnet genesis hash: %s\n", genesis.GetHash().ToString());
        }
        consensus.hashGenesisBlock = genesis.GetHash();

        // cout << consensus.hashGenesisBlock.ToString() << endl;
        // cout << genesis.hashMerkleRoot.ToString() << endl;
        assert(consensus.hashGenesisBlock == uint256S("0xd0349811925ee4b8cfb06fb543a07c230a37a987bf4f8bfa6e2e96041a3ecaf3"));
        assert(genesis.hashMerkleRoot == uint256S("0x72f9d3391b971575a87e1cf679170eef7497f94b8e4999b2e1e6fe38f036bf61"));

        vFixedSeeds.clear(); //!< Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();      //!< Regtest mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true; 
        fTestnetToBeDeprecatedFieldRPC = false;

	checkpointData = (CCheckpointData){
		boost::assign::map_list_of
			( 0, uint256S("0xd0349811925ee4b8cfb06fb543a07c230a37a987bf4f8bfa6e2e96041a3ecaf3"))
            ,
			0,
			0,
			0
	};

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,100);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();
    }

    void UpdateBIP9Parameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
    {
        consensus.vDeployments[d].nStartTime = nStartTime;
        consensus.vDeployments[d].nTimeout = nTimeout;
    }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = 0;

const CChainParams &Params() {
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(const std::string& chain)
{
    if (chain == CBaseChainParams::MAIN)
            return mainParams;
    else if (chain == CBaseChainParams::TESTNET)
            return testNetParams;
    else if (chain == CBaseChainParams::REGTEST)
            return regTestParams;
    else
        throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

void SelectParams(const std::string& network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

void UpdateRegtestBIP9Parameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
{
    regTestParams.UpdateBIP9Parameters(d, nStartTime, nTimeout);
}
 
