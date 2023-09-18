public class Test {
    private static final Find findField = new Find("");
    private int intField = 5;
    protected float[][] someNumb = new float[10][10];
    public double sombeDouble = 3.5;

    public static void main(String[] args) {
        Find newFind = new Find("testField");
        int sum = add(1,2);
        int[][] matrixSum = new int[2][2];
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                matrixSum[i][j] = 1;
            }
        }
        System.out.println(sum);
        System.out.println(getDescription(newFind));
        System.out.println(sum(matrixSum,1.0));
    }

    private static int add(int numb1, int numb2) {
        return numb1+numb2;
    }

    private static String getDescription(Find find)
    {
        return find.desciption;
    }

    private static double sum(int[][] numbers, double mult){
        int sum = 0;
        for (int i = 0; i < numbers.length; i++) {
            for (int j = 0; j < numbers[0].length; j++) {
                sum += numbers[i][j];
            }
        }
        return sum*mult;
    }
    
    /* 
    private static int[][] dummy() {
        int dummy = 0;
        return new int[2][2];
    }
    */
}