import java.util.ArrayList;

public class BackupTest
        extends A
        implements B,
        C
{
    {
        test();
        test();
    }

    private String a2;
    private String a3;
    private String a1;

    void tdfg(int  a,int  b,int  c) {
        main();
    }

    void
    main()
    {
        for (int x = 0; x < 10; x++)
        {
            test();
        }
        if (true)
        {
            test();
            while(true)
            {
                test();
                if (false)
                {
                    test();
                    test(); }
                else
                {
                    test(); }
            } }
        if (5 + 5 > 3)
            test();
        do
        {
            test();
        }
        while (false);
        int y = 5;
        switch(y)
        {
            case 2:
            case 1: System.out.println("AAAA");
                break;
            case 5: System.out.println("BBBB");
                break;
        }
        ArrayList<Integer> testList = new ArrayList<Integer>();
        for (int  x : testList)
        {
            test();}
        try {
            test();
        }
        catch(NullPointerException  e)
        {
            test();
        }
        catch(ArrayIndexOutOfBoundsException  e)
        {
            test();
        }

        finally {
            test();
        }
    }

    String test() {
        return "Hello";
    }

    PluginTest()
    {
        test();
        test();
    }

    class Test {
        private String a1;
        private String a3;

        Test()
        {
            text();
        }

        String
        text()
        {
            Integer x = 5 + 5;
            return x.toString();
        }
    }

    interface TestInterface {}

    enum E implements TestInterface {
        GET2("@") {
            int get() { return 2; }
        }
        , GET1("^") {
            int get() { return 1; }
        }
        , GET3("*") {
            int get() { return 3; }
        }
        , GETN("y") {
            int get() { return 10; }
        };

        E(String str) {
            System.out.println(str);
        }

        E(int x) {
            System.out.println(x);
        }

        abstract int get();

        public int a;
    }
}

/*


*/


/*
public class PluginTest {
    int a;
    String b;
    int c;

    int main() {
        while (true) {
            if (true) {
                System.out.print("asdasas");
            } else {
                test();
                if (5 + 4 == 3) {
                    test();
                }
            }
        }
    }

    String test() {
        try {
            if (9 + 10 == 11) {
                System.out.println("!!!!!");
            }
        } catch (Exception e) {
            test();
        }

        return "5";
    }
}
*/
