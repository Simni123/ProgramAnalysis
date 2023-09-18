package deps.simple;

import deps.util.Utils;

// import some.other.Class;

// Known Dependencies
// -> deps.simple.Other
// -> deps.util.Utils
// -> java.lang.String

/**
 * This is an example class that contains dependencies.
 *
 * Known dependencies:
 */
public class Example {
    Other other = new Other();

    public static void main(String[] args) {
        Utils.printHello();
    }

}
