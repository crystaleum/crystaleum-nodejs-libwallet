#pragma once

#include "deferredtask.h"
#include "walletargs.h"

namespace exawallet {

class CreateWalletTask: public DeferredTask {
public:
    CreateWalletTask(const CreateWalletArgs& args): args_(args) {}

    virtual std::string doWork() override;
    virtual v8::Local<v8::Value> afterWork(std::string& error) override;

private:
    CreateWalletArgs args_;
    Crystaleum::Wallet* wallet_ = nullptr;
};

class OpenWalletTask: public DeferredTask {
public:
    OpenWalletTask(const OpenWalletArgs& args): args_(args) {}

    virtual std::string doWork() override;
    virtual v8::Local<v8::Value> afterWork(std::string& error) override;

private:
    OpenWalletArgs args_;
    Crystaleum::Wallet* wallet_ = nullptr;
};

class CloseWalletTask: public DeferredTask {
public:
    CloseWalletTask(Crystaleum::Wallet* wallet, bool store): wallet_(wallet), store_(store) {}

    virtual std::string doWork() override;
    virtual v8::Local<v8::Value> afterWork(std::string& error) override;

private:
    Crystaleum::Wallet* wallet_ = nullptr;
    bool store_;
};

class RecoveryWalletTask: public DeferredTask {
public:
    RecoveryWalletTask(const RecoveryWalletArgs& args): args_(args) {}

    virtual std::string doWork() override;
    virtual v8::Local<v8::Value> afterWork(std::string& error) override;

private:
    RecoveryWalletArgs args_;
    Crystaleum::Wallet* wallet_ = nullptr;
};


class StoreWalletTask: public DeferredTask {
public:
    StoreWalletTask(Crystaleum::Wallet* wallet): wallet_(wallet) {}

    virtual std::string doWork() override;
    virtual v8::Local<v8::Value> afterWork(std::string& error) override;
private:
    Crystaleum::Wallet* wallet_;
};

class CreateTransactionTask: public DeferredTask {
public:
    CreateTransactionTask(const CreateTransactionArgs& args, Crystaleum::Wallet* wallet): args_(args), wallet_(wallet) {}

    virtual std::string doWork() override;
    virtual v8::Local<v8::Value> afterWork(std::string& error) override;

private:
    CreateTransactionArgs args_;
    Crystaleum::PendingTransaction* transaction_ = nullptr;
    Crystaleum::Wallet* wallet_;
};

class CommitTransactionTask: public DeferredTask {
public:
    CommitTransactionTask(Crystaleum::PendingTransaction* transaction): transaction_(transaction) {}

    virtual std::string doWork() override;
    virtual v8::Local<v8::Value> afterWork(std::string& error) override;

private:
    Crystaleum::PendingTransaction* transaction_;
};

class RestoreMultisigTransactionTask: public DeferredTask {
public:
    RestoreMultisigTransactionTask(const std::string& transactionData, Crystaleum::Wallet* wallet)
        : transactionData_(transactionData), wallet_(wallet) {}

    virtual std::string doWork() override;
    virtual v8::Local<v8::Value> afterWork(std::string& error) override;

private:
    std::string transactionData_;
    Crystaleum::PendingTransaction* transaction_ = nullptr;
    Crystaleum::Wallet* wallet_;
};

} //namespace exawallet
