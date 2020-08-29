import java.util.Scanner

object Main extends App {
  val sc = new Scanner(System.in)

  var N = sc.nextInt()
  var result = false;
  do {
    result |= N % 10 == 7
    N /= 10
  } while (N > 0)
  println(if (result) "Yes" else "No")
}
