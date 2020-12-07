#pragma once

#include <nan.h>

namespace Crystaleum {
struct PendingTransaction;
}

namespace exawallet {

class PendingTransaction : public node::ObjectWrap {
public:
    explicit PendingTransaction(Crystaleum::PendingTransaction* tx): transaction(tx) {}
    virtual ~PendingTransaction();

    static NAN_MODULE_INIT(Init);
    static NAN_METHOD(New);
    static v8::Local<v8::Object> NewInstance(Crystaleum::PendingTransaction* tx);

    static NAN_METHOD(Commit);
    static NAN_METHOD(Amount);
    static NAN_METHOD(Dust);
    static NAN_METHOD(Fee);
    static NAN_METHOD(TransactionsIds);
    static NAN_METHOD(TransactionsCount);

    static NAN_METHOD(MultisigSignData);
    static NAN_METHOD(SignersKeys);
    static NAN_METHOD(SignMultisigTransaction);

private:
    static Nan::Persistent<v8::Function> constructor;

    Crystaleum::PendingTransaction* transaction;
};

}
