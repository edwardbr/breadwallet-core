//
//  BRCryptoWallet.h
//  BRCore
//
//  Created by Ed Gamble on 3/19/19.
//  Copyright © 2019 breadwallet. All rights reserved.
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

#ifndef BRCryptoWallet_h
#define BRCryptoWallet_h

#include "BRCryptoFeeBasis.h"
#include "BRCryptoTransfer.h"

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct BRCryptoWalletRecord *BRCryptoWallet;

    typedef enum {
        CRYPTO_WALLET_STATE_CREATED,
        CRYPTO_WALLET_STATE_DELETED
    } BRCryptoWalletState;

    typedef enum {
        CRYPTO_WALLET_EVENT_CREATED,
        CRYPTO_WALLET_EVENT_CHANGED,
        CRYPTO_WALLET_EVENT_DELETED,

        CRYPTO_WALLET_EVENT_TRANSFER_ADDED,
        CRYPTO_WALLET_EVENT_TRANSFER_CHANGED,
        CRYPTO_WALLET_EVENT_TRANSFER_SUBMITTED,
        CRYPTO_WALLET_EVENT_TRANSFER_DELETED,

        CRYPTO_WALLET_EVENT_BALANCE_UPDATED,
        CRYPTO_WALLET_EVENT_FEE_BASIS_UPDATED,
    } BRCryptoWalletEventType;

    typedef struct {
        BRCryptoWalletEventType type;
        union {
            struct {
                BRCryptoWalletState oldState;
                BRCryptoWalletState newState;
            } state;

            struct {
                /// Handler must 'give'
                BRCryptoTransfer value;
            } transfer;

            struct {
                /// Handler must 'give'
                BRCryptoAmount amount;
            } balanceUpdated;

            struct {
                /// Handler must 'give'
                BRCryptoFeeBasis basis;
            } feeBasisUpdated;
        } u;
    } BRCryptoWalletEvent;

    extern BRCryptoWalletState
    cryptoWalletGetState (BRCryptoWallet wallet);
    
    /**
     * Returns the wallet's currency
     *
     * @param wallet the wallet
     *
     * @return The currency w/ an incremented reference count (aka 'taken')
     */
    extern BRCryptoCurrency
    cryptoWalletGetCurrency (BRCryptoWallet wallet);

    /**
     * Returns the wallet's (default) unit.  Used for *display* of the wallet's balance.
     *
     * @param wallet The wallet
     *
     * @return the unit w/ an incremented reference count (aka 'taken')
     */
    extern BRCryptoUnit
    cryptoWalletGetUnit (BRCryptoWallet wallet);

    /**
     * Returns the wallet's fee unit.
     *
     * @param wallet The wallet
     *
     * @return the fee unit w/ an incremented reference count (aka 'taken')
     */
    extern BRCryptoUnit
    cryptoWalletGetUnitForFee (BRCryptoWallet wallet);
    
    /**
     * Returns the wallets balance
     *
     * @param wallet the wallet
     *
     * @return the balance
     */
   extern BRCryptoAmount
    cryptoWalletGetBalance (BRCryptoWallet wallet);

    extern size_t
    cryptoWalletGetTransferCount (BRCryptoWallet wallet);

    extern BRCryptoBoolean
    cryptoWalletHasTransfer (BRCryptoWallet wallet,
                             BRCryptoTransfer transfer);

    /**
     * Returns the wallet's transfer at `index`.  The index must satisfy [0, count) otherwise
     * an assertion is signaled.
     *
     * @param wallet the wallet
     * @param index the desired transfer index
     *
     * @return The transfer w/ an incremented reference count (aka 'taken')
     */
   extern BRCryptoTransfer
    cryptoWalletGetTransfer (BRCryptoWallet wallet,
                             size_t index);

    extern BRCryptoAddress
    cryptoWalletGetAddress (BRCryptoWallet wallet);

    extern BRCryptoFeeBasis
    cryptoWalletGetDefaultFeeBasis (BRCryptoWallet wallet);

    extern void
    cryptoWalletSetDefaultFeeBasis (BRCryptoWallet wallet,
                                    BRCryptoFeeBasis feeBasis);

    extern BRCryptoTransfer
    cryptoWalletCreateTransfer (BRCryptoWallet wallet,
                                BRCryptoAddress target,
                                BRCryptoAmount amount,
                                BRCryptoFeeBasis feeBasis);
    extern BRCryptoAmount
    cryptoWalletEstimateFee (BRCryptoWallet wallet,
                             BRCryptoAmount amount,
                             BRCryptoFeeBasis feeBasis,
                             BRCryptoUnit feeUnit); // for fee

    extern BRCryptoBoolean
    cryptoWalletEqual (BRCryptoWallet w1, BRCryptoWallet w2);

    DECLARE_CRYPTO_GIVE_TAKE (BRCryptoWallet, cryptoWallet);

#ifdef __cplusplus
}
#endif

#endif /* BRCryptoWallet_h */