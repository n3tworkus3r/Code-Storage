package dao.csv;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;

public class CSVReader {
	private BufferedReader reader;

	public CSVReader(InputStream inputStream) throws IOException {
		reader = new BufferedReader(new InputStreamReader(inputStream, CSVConstants.ENCODING));
	}

	public String[] read() throws IOException {
		String line = reader.readLine();
		if(line != null) {
			return line.split(CSVConstants.SEPARATOR);
		}
		return null;
	}

	public void close() throws IOException {
		reader.close();
	}
}
