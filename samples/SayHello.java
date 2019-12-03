public class SayHello {
    public static void sayHelloTo(String name) {
	System.out.print("Hello ");
	System.out.print(name);
	System.out.println("!");
    }

    public static void sayHelloTimes(String name, int times) {
	while (times > 0) {
	    sayHelloTo(name);
	    times -= 1;
	}
    }

    public static void greetNumber(String greeting, int number) {
	System.out.print(greeting);
	System.out.print(" ");
	System.out.println(number);
    }

    public static void main(String[] args) {
	sayHelloTo("Breno");
	greetNumber("Number", 2);
	sayHelloTimes("Breno", 10);
    }
}
