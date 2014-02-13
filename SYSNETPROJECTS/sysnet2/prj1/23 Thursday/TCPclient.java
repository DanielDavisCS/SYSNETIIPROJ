
/*
 * TCPclient.java
 * Systems and Networks II
 * Project 1
 *
 * This file describes the functions to be implemented by the TCPclient class
 * You may also implement any auxillary functions you deem necessary.
 */
import java.net.*;
import java.io.*;
import java.util.Scanner;

public class TCPclient
{
	private Socket _socket; // the socket for communication with a server
    private OutputStream sendStream;
    private InputStream recvStream;
    
   
       
	/**
	 * Constructs a TCPclient object.
	 */
	public TCPclient()
	{
      
	}

	/**
	 * Creates a streaming socket and connects to a server.
	 *
	 * @param host - the ip or hostname of the server
	 * @param port - the port number of the server
	 *
	 * @return - 0 or a negative number describing an error code if the connection could not be established
	 */
	public int createSocket(String host, int port)
	{
        try{
        _socket = new Socket(host, port);
        sendStream = _socket.getOutputStream();
        recvStream = _socket.getInputStream();
        }catch(Exception ex){
        	System.out.println("Socket stream Fail:");
        	return -1;
        }
        return 0;
	}
    
	/**
	 * Sends a request for service to the server. Do not wait for a reply in this function. This will be
	 * an asynchronous call to the server.
	 *
	 * @request - the request to be sent
	 *
	 * @return - 0, if no error; otherwise, a negative number indicating the error
	 */
	public int sendRequest(String request)
	{
	if(request.length() == 0)return -1;
        try{
            byte[] sendBuff = new byte[request.length()];
            sendBuff = request.getBytes();
            sendStream.write(sendBuff, 0, sendBuff.length);
        }catch(IOException ex){
            System.err.println("IOException in sendRequst");
        	return -1;
	}
		return 0;
	}

	/**
	 * Receives the server's response. Also displays the response in a
	 * clear and concise format.
	 *
	 * @return - the server's response or NULL if an error occured
	 */
	public String receiveResponse()
	{
		String response = "";		
		try{
            int dataSize;
            while((dataSize = recvStream.available()) == 0);
            byte[] recvBuff = new byte[dataSize];
            recvStream.read(recvBuff, 0,dataSize);
            response = new String(recvBuff,0,dataSize);
        }catch (Exception ex){
            System.err.println("IOException in sendResponse");
        	return null;
	}
		return response;
	}
	
	/*
     * Prints the response to the screen in a formatted way.
     *
     * response - the server's response as an XML formatted string
     *
     */
	public static void printResponse(String response)
	{
		System.out.println("Response from server: " + response);  
	}
    
    
	/*
	 * Closes an open socket.
	 *
     * @return - 0, if no error; otherwise, a negative number indicating the error
	 */
	public int closeSocket()
	{
		try{    
		    sendStream.close();  
		    recvStream.close();    	
		    _socket.close();    
		}catch(Exception ex){  
		    System.err.println("IOException in close"); 
			return -1;
		}   
		return 0;
	}
    
	
	/**
	 * The main function. Use this function for
	 * testing your code. We will use our own main function for testing.
	 */
	public static void main(String[] args)
	{
		String response ="";
		if (args.length > 0) {	 
			final String servName = args[0];
		    final int servPort = Integer.parseInt(args[1]);	
		    TCPclient client = new TCPclient();  
		    client.createSocket(servName, servPort); 
		    
		   if(client.sendRequest("<echo>sfglk</echo>") >= 0 ){    
		    response = client.receiveResponse();    
		    client.printResponse(response);    
		}	  
		   if(client.sendRequest("") >= 0 ){  
		    response = client.receiveResponse();    
		    client.printResponse(response);    
		}
		    
		   if(client.sendRequest("<echo>sf\nglk</echo>") >= 0 ){    
		    response = client.receiveResponse();    
		    client.printResponse(response);
			}    
		
	  	    client.closeSocket();    
		}
	}
    
}



