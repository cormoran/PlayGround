package com.example.thrift;

import org.apache.thrift.TException;
import org.apache.thrift.async.AsyncMethodCallback;

public class ThriftServiceImpl implements ThriftService.AsyncIface {

    @Override
    public void func(int num, AsyncMethodCallback<Integer> resultHandler) throws TException {
        resultHandler.onComplete(10);
        resultHandler.onError(new IllegalArgumentException());
        resultHandler.onComplete(11);
        resultHandler.onError(new IllegalArgumentException());
    }

}
