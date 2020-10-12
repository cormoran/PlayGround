package decatontest;

import java.util.Properties;
import java.util.concurrent.CompletableFuture;

import com.linecorp.decaton.client.DecatonClient;
import com.linecorp.decaton.client.PutTaskResult;
import com.linecorp.decaton.protobuf.ProtocolBuffersSerializer;

import org.apache.kafka.clients.producer.ProducerConfig;

import decatontest.Task.PrintMessageTask;

public final class ProducerMain {
    public static void main(String[] args) throws Exception {
        try (DecatonClient<PrintMessageTask> client = newClient()) {
            for (int i = 0; i < 100000; i++) {
                String name = args[0];
                int age = Integer.parseInt(args[1]);
                PrintMessageTask task = PrintMessageTask.newBuilder().setName(name).setAge(age).build();
                CompletableFuture<PutTaskResult> result = client.put(name, task); // (1)

                // Synchronously wait the result
                result.join();
                // Asynchronously observe the result
                result.whenComplete((r, e) -> {
                    System.err.println("Producing task failed... " + e);
                });
            }
        }
    }

    private static DecatonClient<PrintMessageTask> newClient() {
        Properties producerConfig = new Properties();
        producerConfig.setProperty(ProducerConfig.CLIENT_ID_CONFIG, "my-decaton-client");
        producerConfig.setProperty(ProducerConfig.BOOTSTRAP_SERVERS_CONFIG, System.getProperty("bootstrap.servers"));

        return DecatonClient.producing("test", new ProtocolBuffersSerializer<PrintMessageTask>()).applicationId("MyApp") // (2)
                // By default it sets local hostname but here we go explicit
                .instanceId("localhost").producerConfig(producerConfig).build();
    }
}