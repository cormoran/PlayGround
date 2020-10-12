package decatontest;

import com.linecorp.decaton.processor.DecatonProcessor;
import com.linecorp.decaton.processor.ProcessingContext;

import decatontest.Task.PrintMessageTask;

public class PrintMessageTaskProcessor implements DecatonProcessor<PrintMessageTask> {
    @Override
    public void process(ProcessingContext<PrintMessageTask> context, PrintMessageTask task)
            throws InterruptedException {
        Thread.sleep(100);
        System.out.println("hello");
        System.out.println(task);
        return;
    }
}
