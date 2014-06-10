import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.RandomAccessFile;
import java.math.BigInteger;
import java.nio.file.DirectoryNotEmptyException;
import java.nio.file.Files;
import java.nio.file.NoSuchFileException;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Scanner;


public class  DuplicateAndRemove {
	private static MessageDigest md;

	static {
		try {
			md = MessageDigest.getInstance("SHA-512");
		} catch (NoSuchAlgorithmException e) {
			throw new RuntimeException("cannot initialize SHA-512 hash function", e);
		}
	}

	public static void find(Map<String, List<String>> lists, File directory, boolean lean) throws Exception 
	{
		String hash;
		File[] fList = directory.listFiles();
		
		for (File child : fList) {
			if (child.isDirectory()) {
				find(lists, child, lean);
			} 
			else 
			{
				try {
					hash = lean ? makeHash1(child) : makeHash2(child);
					List<String> list = lists.get(hash);
					
					if (list == null) {
						list = new LinkedList<String>();
						lists.put(hash, list);
					}
					
					list.add(child.getAbsolutePath());
				} catch (IOException e) {
					throw new RuntimeException("cannot read file " + child.getAbsolutePath(), e);
				}
			}
		}
	}

	
	public static String makeHash2(File infile) throws Exception {
		FileInputStream fin = new FileInputStream(infile);
		byte data[] = new byte[(int) infile.length()];
		
		fin.read(data);
		fin.close();
		
		String hash = new BigInteger(1, md.digest(data)).toString(16);
		return hash;
	}

	
	public static String makeHash1(File infile) throws Exception {
		RandomAccessFile file = new RandomAccessFile(infile, "r");

		int buffSize = 16384;
		byte[] buffer = new byte[buffSize];
		long read = 0;

		// calculate the hash of the whole file for the test
		long offset = file.length();
		int unitsize;
		
		while (read < offset) {
			unitsize = (int) (((offset - read) >= buffSize) ? buffSize	: (offset - read));
			file.read(buffer, 0, unitsize);
			md.update(buffer, 0, unitsize);
			read += unitsize;
		}

		file.close();
		String hash = new BigInteger(1, md.digest()).toString(16);
		return hash;
	}


	public static void main(String[] args) {
		if (args.length < 1) {
			System.out.println("Please supply a path to directory to find duplicate files in.");
			return;
		}
		
		File dir = new File(args[0]);
		if (!dir.isDirectory()) {
			System.out.println("Supplied directory does not exist.");
			return;
		}
		
		Map<String, List<String>> lists = new HashMap<String, List<String>>();
		
		try {
			DuplicateAndRemove.find(lists, dir, args.length == 1 || !args[1].equals("-quick"));
		} catch (Exception e) {
			e.printStackTrace();
		}
		
		//Display the duplicate files
		System.out.println("Duplicate files found :-");
		for (List<String> list : lists.values()) 
		{
			if (list.size() > 1) 
			{
				System.out.println("------------------");
				for (String file : list) 
				{
					System.out.println(file);
				}
			}
		}
		System.out.println("------------------");

		String dis= "Yes";

		Scanner input = new Scanner(System.in);
		System.out.println("Do you wish to delete duplicate files?");
		dis=input.nextLine();

		if(dis.equalsIgnoreCase("yes"))
		{
			System.out.println("Enter the path to duplicate file : ");
			String p="";
			p = input.nextLine();
			Path path = Paths.get(p);

			try {
				Files.delete(path);
			} catch (NoSuchFileException x) {
				System.err.format("%s: no such" + " file or directory%n", path);
			} catch (DirectoryNotEmptyException x) {
				System.err.format("%s not empty%n", path);
			} catch (IOException x) {
				// File permission problems are caught here.
				System.err.println(x);
			}
		}
		
		input.close();
	}
}

