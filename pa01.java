// Scanner Library
import java.io.File;
import java.io.IOException;
import java.util.Scanner;

public class pa01 {
    public static void main(String[] args) throws IOException {
        // Create string for key, plaintext and scan in key and plaintext
        String key = "";
        String plaintext = "";

        // Create scanner for key and plaintext
        Scanner keyScan = new Scanner(new File(args[0]));
        Scanner plaintextScan = new Scanner(new File(args[1]));

        // Take in key from key scan until end of file
        while (keyScan.hasNextLine()) {
            key += keyScan.nextLine();
        }

        // Take in plaintext from plaintext scan until end of file
        while (plaintextScan.hasNextLine()) {
            plaintext += plaintextScan.nextLine();
        }

        // Convert key and plaintext to lowercase
        key = key.toLowerCase();
        plaintext = plaintext.toLowerCase();

        // Remove all non-alphabetic characters from key and plaintext
        key = key.replaceAll("[^a-zA-Z]", "");
        plaintext = plaintext.replaceAll("[^a-zA-Z]", "");

        // Add X for padding till the plain text length reaches 512
        while (plaintext.length() < 512) {
            plaintext += "x";
        }

        // Convert key and plaintext from char to int
        int[] keyInt = new int[key.length()];
        int[] plaintextInt = new int[plaintext.length()];

        // Converting key into int
        for (int i = 0; i < key.length(); i++) {
            keyInt[i] = (int) key.charAt(i) - 97;
        }

        // Converting plaintext into int
        for (int i = 0; i < plaintext.length(); i++) {
            plaintextInt[i] = (int) plaintext.charAt(i) - 97;
        }

        // Create ciphertext char array and int array
        char[] ciphertext = new char[512]; 
        int[] ciphertextInt = new int[512];

        // Encrypting plaintext into ciphertext
        for (int i = 0, j = 0; i < 512; i++, j++) {
            if(j == key.length()) {
                j = 0;
            }

            ciphertextInt[i] = (plaintextInt[i] + keyInt[j]) % 26;

        }

        for(int i = 0; i < 512; i++) {
            ciphertext[i] = (char) (ciphertextInt[i] + 97);
        }

        // Print out ciphertext
        for (int i = 0; i < 512; i++) {
            System.out.print(ciphertext[i]);
            if ((i + 1) % 80 == 0) {
                System.out.println();
            }
        }

        System.out.println();

    }
  }