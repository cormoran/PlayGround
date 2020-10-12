package decatontest;

import java.util.Properties;

import com.linecorp.decaton.processor.ProcessorProperties;
import com.linecorp.decaton.processor.ProcessorsBuilder;
import com.linecorp.decaton.processor.Property;
import com.linecorp.decaton.processor.StaticPropertySupplier;
import com.linecorp.decaton.processor.runtime.ProcessorSubscription;
import com.linecorp.decaton.processor.runtime.SubscriptionBuilder;
import com.linecorp.decaton.protobuf.ProtocolBuffersDeserializer;

import org.apache.kafka.clients.consumer.ConsumerConfig;

import decatontest.Task.PrintMessageTask;

public final class ProcessorMain {
    public static void main(String[] args) throws Exception {
        Properties consumerConfig = new Properties();
        consumerConfig.setProperty(ConsumerConfig.CLIENT_ID_CONFIG, "my-decaton-processor");
        consumerConfig.setProperty(ConsumerConfig.BOOTSTRAP_SERVERS_CONFIG, System.getProperty("bootstrap.servers"));
        consumerConfig.setProperty(ConsumerConfig.GROUP_ID_CONFIG, "my-decaton-processor");

        ProcessorSubscription subscription = SubscriptionBuilder.newBuilder("my-decaton-processor") // (1)
                .processorsBuilder(ProcessorsBuilder
                        .consuming("test", new ProtocolBuffersDeserializer<>(PrintMessageTask.parser()))
                        .thenProcess(new PrintMessageTaskProcessor()))
                .properties(StaticPropertySupplier
                        .of(Property.ofStatic(ProcessorProperties.CONFIG_PARTITION_CONCURRENCY, 300)))
                .consumerConfig(consumerConfig).buildAndStart();

        Thread.sleep(30000);
        subscription.close();
    }
}