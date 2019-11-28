//
//  BRChainParams.c
//  BRCore
//
//  Created by Aaron Voisine on 3/11/19.
//  Copyright (c) 2019 breadwallet LLC
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.

#include "BRChainParams.h"

static const char *BRMainNetDNSSeeds[] = {
    /*"seed.bitcoinsv.io.",
    "seed.bitprim.org.",
    "seed.cascharia.com.",
    "seed.satoshisvision.network.",*/
    "127.0.0.1",
    NULL};

static const char *BRTestNetDNSSeeds[] = {
    "testnet-seed.bitcoinsv.io.",
    "testnet-seed.bitprim.org.", "testnet-seed.deadalnix.me.",
    "testnet-seeder.criptolayer.net.", NULL};

// blockchain checkpoints - these are also used as starting points for partial chain downloads, so they must be at
// difficulty transition boundaries in order to verify the block difficulty at the immediately following transition
static const BRCheckPoint BRMainNetCheckpoints[] = {
    {      0, uint256("000000000019d6689c085ae165831e934ff763ae46a2a6c172b3f1b60a8ce26f"), 1231006505, 0x1d00ffff }
//{ 604800,
};

static const BRCheckPoint BRTestNetCheckpoints[] = {
    {       0, uint256("000000000933ea01ad0ee984209779baaec3ced90fa3f408719526f8d77f4943"), 1296688602, 0x1d00ffff }
    //{ 1512000,
};

static int BRMainNetVerifyDifficulty(const BRMerkleBlock *block, const BRSet *blockSet)
{
    const BRMerkleBlock *previous, *b = NULL;
    uint32_t i;

    assert(block != NULL);
    assert(blockSet != NULL);

    // check if we hit a difficulty transition, and find previous transition block
    if ((block->height % BLOCK_DIFFICULTY_INTERVAL) == 0) {
        for (i = 0, b = block; b && i < BLOCK_DIFFICULTY_INTERVAL; i++) {
            b = BRSetGet(blockSet, &b->prevBlock);
        }
    }

    previous = BRSetGet(blockSet, &block->prevBlock);
    return BRMerkleBlockVerifyDifficulty(block, previous, (b) ? b->timestamp : 0);
}

static int BRTestNetVerifyDifficulty(const BRMerkleBlock *block, const BRSet *blockSet)
{
    return 1; // XXX skip testnet difficulty check for now
}

extern const BRCheckPoint *BRChainParamsGetCheckpointBefore (const BRChainParams *params, uint32_t timestamp) {
    for (ssize_t index = params->checkpointsCount - 1; index >= 0; index--)
        if (params->checkpoints[index].timestamp < timestamp)
            return &params->checkpoints[index];
   return NULL;
}

extern const BRCheckPoint *BRChainParamsGetCheckpointBeforeBlockNumber (const BRChainParams *params, uint32_t blockNumber) {
    for (ssize_t index = params->checkpointsCount - 1; index >= 0; index--)
        if (params->checkpoints[index].height < blockNumber)
            return &params->checkpoints[index];
   return NULL;
}

static const BRChainParams BRMainNetParamsRecord = {
    BRMainNetDNSSeeds,
    8333,                  // standardPort
    0xe8f3e1e3,            // magicNumber
    0, // services
    BRMainNetVerifyDifficulty,
    BRMainNetCheckpoints,
    sizeof(BRMainNetCheckpoints)/sizeof(*BRMainNetCheckpoints),
    { BITCOIN_PUBKEY_PREFIX, BITCOIN_SCRIPT_PREFIX, BITCOIN_PRIVKEY_PREFIX, BITCOIN_BECH32_PREFIX },
    BITCOIN_FORKID
};
const BRChainParams *BRMainNetParams = &BRMainNetParamsRecord;

static const BRChainParams BRTestNetParamsRecord = {
    BRTestNetDNSSeeds,
    18333,                 // standardPort
    0xf4f3e5f4,            // magicNumber
    0, // services
    BRTestNetVerifyDifficulty,
    BRTestNetCheckpoints,
    sizeof(BRTestNetCheckpoints)/sizeof(*BRTestNetCheckpoints),
    { BITCOIN_PUBKEY_PREFIX_TEST, BITCOIN_SCRIPT_PREFIX_TEST, BITCOIN_PRIVKEY_PREFIX_TEST, BITCOIN_BECH32_PREFIX_TEST },
    BITCOIN_FORKID
};

const BRChainParams *BRTestNetParams = &BRTestNetParamsRecord;
