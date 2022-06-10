package dao.csv;

import java.io.BufferedWriter;
import java.io.IOException;
import java.io.OutputStream;
import java.io.OutputStreamWriter;

public class CSVWriter {
	private BufferedWriter writer;

	public CSVWriter(OutputStream outputStream) throws IOException {
		writer = new BufferedWriter(new OutputStreamWriter(outputStream, CSVConstants.ENCODING));
	}

	public void write(String[] cells) throws IOException {
		boolean isNotFirst = false;
		for(String cell : cells) {
			if(isNotFirst) {
				writer.write(CSVConstants.SEPARATOR);
			} else {
				isNotFirst = true;
			}
			writer.write(cell);
		}
		writer.newLine();
	}

	public void flush() throws IOException {
		writer.flush();
	}

	public void close() throws IOException {
		writer.close();
	}
}
