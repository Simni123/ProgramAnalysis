import java.io.File;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Scanner;
import java.util.Set;
import java.util.regex.*;

public class Search {
    public static void main(String[] args) throws Exception {
        //Find all project files
        List<File> allFiles = new ArrayList<>();
        String dir = "src\\deps";
        String pattern = "(\\.java)$";
        listf(dir, allFiles, pattern);

        //finding All file dependencies call dependencies
        Set<String> fileDependencies;
        System.out.println("Result:");
        for (File file : allFiles) {
            fileDependencies = findDependencies(file);
            System.out.print(file.getName() + ": ");
            for (String string : fileDependencies) {
                System.out.print(string + ", ");
            }
            System.out.println();
        }
        
        //Showing result of one file dependencies
        /* 
        for (File file : allFiles) {
            System.out.println(file.getName());
        }
        */
    }

    public static void listf(String directoryName, List<File> files, String pattern) {
        File directory = new File(directoryName);

        // Get all files from a directory.
        File[] fList = directory.listFiles();
        Pattern pat = Pattern.compile(pattern);
        if(fList != null) {
            for (File file : fList) {      
                if (file.isFile()) {
                    Matcher matcher = pat.matcher(file.getName());
                    if (matcher.find()) files.add(file);
                } else if (file.isDirectory()) {
                    listf(file.getAbsolutePath(), files, pattern);
                }
            }
        }
    }

    public static Set<String> findDependencies(File file) {
        try {
            Set<String> dependencies = new HashSet();
            //System.out.println(file.getName());
            
            //Reading the full file
            Scanner reader = new Scanner(file);
            Boolean sectionCommend = false;
            while (reader.hasNextLine()) {
                String readLine = reader.nextLine();
                Pattern pat;
                Matcher matcher;

                //Skipping line comment
                readLine = removeMatchingSubstring(readLine, "\\/\\/.*");
                
                //skipping if in section commend
                pat = Pattern.compile(".*\\*\\/");
                matcher = pat.matcher(readLine);
                if (matcher.find()) {
                    readLine = matcher.replaceAll("");
                    sectionCommend = false;
                }
                if (sectionCommend == true) continue;

                //Taking out string content
                readLine = removeMatchingSubstring(readLine, "(\\\".*?\\\")");

                //Taking out one line /* contet */ structures
                readLine = removeMatchingSubstring(readLine, "(\\/\\*.*?\\*\\/)");

                //Skipping section comments 
                pat = Pattern.compile("\\/\\*.*");
                matcher = pat.matcher(readLine);
                if (matcher.find()) {
                    sectionCommend = true;
                    readLine = matcher.replaceAll("");
                }

                // For the posability of more precise conditions than starts with upper case
                /* 
                //finding imports declerations
                importsRegex = "import";
                pat = Pattern.compile(importsRegex);
                matcher = pat.matcher(readLine);
                if(matcher.find()) {
                    String[] splitStrinvg = readLine.split("import ");
                    String dependency = splitStrinvg[1];
                    dependencies.add(dependency.trim());
                    System.out.println(dependency);
                }
                */

                //System.out.println(readLine);

                //finding all remaining which stat with upper case
                pat = Pattern.compile("(\\b[A-Z][A-Za-z]*\\b)");
                matcher = pat.matcher(readLine);
                if (matcher.find() && !matcher.group(1).equals("Override")) dependencies.add(matcher.group(1));

            }
            return dependencies;
        } catch (Exception e) {
            e.printStackTrace();
            return null;
        }
    }

    public static String removeMatchingSubstring(String input, String regexPattern) {
        // Create a Pattern object from the regex pattern
        Pattern pattern = Pattern.compile(regexPattern);
        
        // Use a Matcher to find and replace all matching substrings with an empty string
        Matcher matcher = pattern.matcher(input);
        String result = matcher.replaceAll("");

        return result;
    }

}
