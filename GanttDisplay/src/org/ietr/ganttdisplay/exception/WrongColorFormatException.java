/**
 * 
 */
package org.ietr.ganttdisplay.exception;

/**
 * Exception thrown when no file name was found in the command line
 * 
 * @author mpelcat
 */
public class WrongColorFormatException extends Exception {

	/**
	 * The string that does not contain a correct color format (#rrggbb)
	 */
	private String wrongString = null;

	private static final long serialVersionUID = -7306885684800763239L;

	
	public WrongColorFormatException(String wrongString) {
		super();
		this.wrongString = wrongString;
	}


	@Override
	public String getMessage() {
		return "Wrong color expression (should be of type #rrggbb): " + wrongString;
	}

	
}
