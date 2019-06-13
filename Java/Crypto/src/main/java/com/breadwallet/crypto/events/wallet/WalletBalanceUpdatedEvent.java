/*
 * Created by Michael Carrara <michael.carrara@breadwallet.com> on 5/31/18.
 * Copyright (c) 2018 Breadwinner AG.  All right reserved.
 *
 * See the LICENSE file at the project root for license information.
 * See the CONTRIBUTORS file at the project root for a list of contributors.
 */
package com.breadwallet.crypto.events.wallet;

import com.breadwallet.crypto.Amount;

public final class WalletBalanceUpdatedEvent implements WalletEvent {

    private final Amount balance;

    public WalletBalanceUpdatedEvent(Amount balance) {
        this.balance = balance;
    }

    public Amount getBalance() {
        return balance;
    }

    @Override
    public <T> T accept(WalletEventVisitor<T> visitor) {
        return visitor.visit(this);
    }
}