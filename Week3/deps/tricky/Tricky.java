package deps.tricky;
// This class is a little more tricky.
// It has many dependencies but none to Other :D.
//
// -> dtu.deps.simple.Example
// -> dtu.deps.util.Utils

import deps.simple.*;
import deps.util.*;

public class Tricky {
    Example /* System */ Other = new Example();

    Tricky deps, simple;

    private <Other> void hello(/*dtu.deps.simple.Other*/ Utils Other) {
        Tricky dtu = new Tricky();
        deps.simple.Other = new Example();
    }
    private <Other> void Other(Other Other) {
        return;
    }
}