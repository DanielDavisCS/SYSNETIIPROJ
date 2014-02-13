import java.net.DatagramSocket;

/*
 * UDPclient.java
 * Systems and Networks II
 * Project 2
 *
 * This file describes the functions to be implemented by the UDPclient class
 * You may also implement any auxillary functions you deem necessary.
 */

public class UDPclient
{
	private DatagramSocket _socket; // the socket for communication with a server
	
	/**
	 * Constructs a TCPclient object.
	 */
	public UDPclient()
	{
	}
	
	/**
	 * Creates a datagram socket and binds it to a free port.
	 *
	 * @return - 0 or a negative number describing an error code if the connection could not be established
	 */
	public int createSocket()
	{
		
	}

	/**
	 * Sends a request for service to the server. Do not wait for a reply in this function. This will be
	 * an asynchronous call to the server.
	 * 
	 * @param request - the request to be sent
	 * @param hostAddr - the ip or hostname of the server
	 * @param port - the port number of the server
	 *
	 * @return - 0, if no error; otherwise, a negative number indicating the error
	 */
	public int sendRequest(String request, String hostAddr, int port)
	{
		
	}
	
	/**
	 * Receives the server's response following a previously sent request.
	 *
	 * @return - the server's response or NULL if an error occured
	 */
	public String receiveResponse()
	{
		
	}
	
	/*
    * Prints the response to the screen in a formatted way.
    *
    * response - the server's response as an XML formatted string
    *
    */
	public static void printResponse(String response)
	{
	
	}
 

	/*
	 * Closes an open socket.
	 *
    * @return - 0, if no error; otherwise, a negative number indicating the error
	 */
	public int closeSocket() 
	{
		
	}

	/**
	 * The main function. Use this function for 
	 * testing your code. We will provide a new main function on the day of the lab demo.
	 */
	public static void main(String[] args)
	{
		
	}

}
