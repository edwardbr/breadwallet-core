//
//  CoreTests-Bridging-Header.h
//  BRCore
//
//  Created by Ed Gamble on 3/19/19.
//  Copyright © 2019 breadwallet. All rights reserved.
//
//  See the LICENSE file at the project root for license information.
//  See the CONTRIBUTORS file at the project root for a list of contributors.


//
//  Use this file to import your target's public headers that you would like to expose to Swift.
//
#include "ethereum/BREthereum.h"
#include "crypto/BRCryptoAccount.h"
#include "crypto/BRCryptoAmount.h"
#include "crypto/BRCryptoCurrency.h"
#include "crypto/BRCryptoNetwork.h"
#include "crypto/BRCryptoPrivate.h"
#include "crypto/BRCryptoUnit.h"

// Bitcoin
extern int BRRunSupTests (void);

extern int BRRunTests();

//non breaking change for the Java/Swift crew
//if you set isBTC to IS_BSV you will be testing bsv
#define IS_BCH 0
#define IS_BTC 1
#define IS_BSV 2

extern int BRRunTestsSync (const char *paperKey,
                           int isBTC,
                           int isMainnet);

extern int BRRunTestWalletManagerSync (const char *paperKey,
                                       const char *storagePath,
                                       int isBTC,
                                       int isMainnet);

extern int BRRunTestWalletManagerSyncStress(const char *paperKey,
                                            const char *storagePath,
                                            uint32_t earliestKeyTime,
                                            uint64_t blockHeight,
                                            int isBTC,
                                            int isMainnet);

extern int BRRunTestsBWM (const char *paperKey,
                          const char *storagePath,
                          int isBTC,
                          int isMainnet);

extern void BRRandInit (void);

// testCrypto.c
extern void runCryptoTests (void);

extern BRCryptoBoolean runCryptoTestsWithAccountAndNetwork (BRCryptoAccount account,
                                                            BRCryptoNetwork network,
                                                            const char *storagePath);

// Ripple
extern void
runRippleTest (void /* ... */);

#include "test.h"

