/*
 * This Java source file was generated by the Gradle 'init' task.
 */
package rxjava.test;

import java.util.concurrent.Executor;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;

import org.springframework.scheduling.concurrent.ThreadPoolTaskExecutor;

import io.reactivex.Flowable;
import io.reactivex.Observable;
import io.reactivex.disposables.Disposable;
import io.reactivex.schedulers.Schedulers;

public class App {
    public String getGreeting() {
        return "Hello world.";
    }

    public static void main(String[] args) throws InterruptedException {
        Executor executor = Executors.newFixedThreadPool(40);

        Disposable dis = Flowable.range(1, 10).subscribeOn(Schedulers.single()).parallel(10)
                .runOn(Schedulers.from(executor)).map(i -> {
                    System.out.println("map " + i + " on " + Thread.currentThread().getName());
                    System.out.println("sleep start" + i);
                    Thread.sleep(100);
                    System.out.println("sleep end" + i);
                    return i;
                }).sequential().reduce(0, (sum, i) -> {
                    System.out.println("reduce " + i + " on " + Thread.currentThread().getName());
                    return sum + i;
                }).subscribe();
        Observable.timer(2000, TimeUnit.MILLISECONDS).subscribeOn(Schedulers.single()).subscribe((a) -> {
            System.out.println("disposed: " + dis.isDisposed());
            dis.dispose();
        });
        System.out.println("end!!!!!!!!!!!!!!!!!!");
        Thread.sleep(100000);
    }
}
