#include "wallettasks.h"

#include "wallet.h"
#include "pendingtransaction.h"

namespace exawallet {

using namespace v8;

std::string CreateWalletTask::doWork() {
    auto manager = Crystaleum::WalletManagerFactory::getWalletManager();
    if (manager->walletExists(args_.path)) {
        return "Wallet already exists: " + args_.path;
    }

    wallet_ = manager->createWallet(args_.path, args_.password, args_.language, args_.nettype);

    if (!wallet_) {
        return "WalletManager returned null wallet pointer";
    }

    if (!wallet_->errorString().empty()) {
        return wallet_->errorString();
    }

    if (!wallet_->init(args_.daemonAddress)) {
        return "Couldn't init wallet";
    }

    wallet_->setTrustedDaemon(true);
    wallet_->startRefresh();
    return {};
}

Local<Value> CreateWalletTask::afterWork(std::string& error) {
    return Wallet::NewInstance(wallet_);
}

std::string OpenWalletTask::doWork() {
    auto manager = Crystaleum::WalletManagerFactory::getWalletManager();
    if (!manager->walletExists(args_.path)) {
        return "wallet does not exist: " + args_.path;
    }

    wallet_ = manager->openWallet(args_.path, args_.password, args_.nettype);

    if (!wallet_) {
        return "WalletManager returned null wallet pointer";
    }

    if (!wallet_->errorString().empty()) {
        return wallet_->errorString();
    }

    if (!wallet_->init(args_.daemonAddress)) {
        return "Couldn't init wallet";
    }

    wallet_->setTrustedDaemon(true);
    wallet_->startRefresh();
    return {};
}

Local<Value> OpenWalletTask::afterWork(std::string& error) {
    return Wallet::NewInstance(wallet_);
}

std::string CloseWalletTask::doWork() {
    auto manager = Crystaleum::WalletManagerFactory::getWalletManager();
    manager->closeWallet(wallet_, store_);
    return {};
}

Local<Value> CloseWalletTask::afterWork(std::string& error) {
    return Nan::Undefined();
}

std::string RecoveryWalletTask::doWork() {
    auto manager = Crystaleum::WalletManagerFactory::getWalletManager();

    wallet_ = manager->recoveryWallet(args_.path,
                                       args_.password,
                                       args_.mnemonic,
                                       args_.nettype,
                                       args_.restoreHeight);

    if (!wallet_) {
        return "WalletManager returned null wallet pointer";
    }

    if (!wallet_->errorString().empty()) {
        return wallet_->errorString();
    }
    
    if (!wallet_->init(args_.daemonAddress)) {
        return "Couldn't init wallet";
    }

    wallet_->setTrustedDaemon(true);
    wallet_->startRefresh();
    return {};
}

Local<Value> RecoveryWalletTask::afterWork(std::string& error) {
    return Wallet::NewInstance(wallet_);
}

std::string StoreWalletTask::doWork() {
    if (!wallet_->store(wallet_->path())) {
        return "Couldn't store wallet";
    }

    return {};
}
Local<Value> StoreWalletTask::afterWork(std::string& error) {
    return Nan::Undefined();
}

std::string CreateTransactionTask::doWork() {
    transaction_ = wallet_->createTransaction(args_.address, args_.paymentId, args_.amount, args_.mixin);
    if (!wallet_->errorString().empty()) {
        return wallet_->errorString();
    }

    return {};
}

Local<Value> CreateTransactionTask::afterWork(std::string& error) {
    return PendingTransaction::NewInstance(transaction_);
}

std::string CommitTransactionTask::doWork() {
    if (!transaction_->commit()) {
        return "Couldn't commit transaction: " + transaction_->errorString();
    }

    return {};
}

Local<Value> CommitTransactionTask::afterWork(std::string& error) {
    return Nan::Undefined();
}

std::string RestoreMultisigTransactionTask::doWork() {
    transaction_ = wallet_->restoreMultisigTransaction(transactionData_);
    if (!wallet_->errorString().empty()) {
        return wallet_->errorString();
    }
    
    return {};
}

Local<Value> RestoreMultisigTransactionTask::afterWork(std::string& error) {
    return PendingTransaction::NewInstance(transaction_);
}

}
