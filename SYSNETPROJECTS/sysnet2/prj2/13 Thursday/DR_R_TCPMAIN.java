/*
 * TCPmain.java
 * Systems and Networks II
 * Project 1
 *
 * This file implements the test program.
 */

import java.io.*;
import java.net.*;

public class DR_R_TCPMAIN 
{
	

    /**
     * The main function. Use this function for testing your code. We will use
     * our own main function for testing.
     */
    public static void main(String[] args) 
	{
        UDPclient client = new UDPclient();
        String serverName;
		
		if (args.length != 2) {
			System.err.println("Usage: TCPclient <serverName> <port number>\n");
			return;
		}
        try {
            serverName = args[0];
        } catch (NullPointerException xcp) {
            System.err.println("Usage: TCPclient <serverName> <port number>\n");
            return;
        }

        int portNum;
        try {
            portNum = Integer.parseInt(args[1]);
        } catch (NumberFormatException xcp) {
            System.err.println("Usage: TCPclient <serverName> <port number>\n");
            return;
        }

        // run tests
		if (!runTest (serverName, portNum, "<loadavg/>", null))
			System.out.println ("Failed test 1.\n");
		else
			System.out.println ("Passed test 1.\n\n");
		
		if (!runTest (serverName, portNum, "<echo>Hello World!</echo>", "<reply>Hello World!</reply>"))
			System.out.println ("Failed test 2.\n");
		else
			System.out.println ("Passed test 2.\n\n");
		
		if (!runTest (serverName, portNum, "<echo></echo>", "<reply></reply>"))
			System.out.println ("Failed test 3.\n");
		else
			System.out.println ("Passed test 3.\n\n");
		
		if (!runTest (serverName, portNum, "<echo>Bye Bye World...<echo>", "<error>unknown format</error>"))
			System.out.println ("Failed test 4.\n");
		else
			System.out.println ("Passed test 4.\n\n");
		
		if (!runTest (serverName, portNum, "", "<error>unknown format</error>"))
			System.out.println ("Failed test 5.\n");
		else
			System.out.println ("Passed test 5.\n");
			
			
		/*
		*	Additional Test
		*/
		
		if (!runTest (serverName, portNum, "<echo></echo> ", "<error>unknown format</error>"))
			System.out.println ("Failed test 6.\n");
		else
			System.out.println ("Passed test 6.\n");
		
		if (!runTest (serverName, portNum, "\n", "<error>unknown format</error>"))
			System.out.println ("Failed test 7.\n");
		else
			System.out.println ("Passed test 7.\n");
			
		if (!runTest (serverName, portNum, "<shutdown/>", ""))
			System.out.println ("Failed test 8 - Shutdown.\n");
		else
			System.out.println ("Passed test 8 - Shutdown.\n");
		
		if (!runTest (serverName, portNum, "<shutdown/>", ""))
			System.out.println ("Failed test 9 - Time Out.\n");
		else
			System.out.println ("Passed test 9 - Time Out.\n");
	}
    
	/**
	 * Runs a test by sending a message to the server and comparing the result to the expected result.
	 *
	 * hostname  - the ip address or hostname of the server given as a string
	 * portNum   - the port number of the server
	 * req       - the message for the server
	 * expctResp - the expected response from the server or null if any response is accepted
	 * 
	 * returns true if the expected value matches the return value and false otherwise
	 */
	private static boolean runTest (String hostname, int portNum, String req, String expctResp)
	{
		UDPclient client = new UDPclient();
		
		if (client.createSocket() < 0)
            return false;
        

        if (client.sendRequest(req, hostname , portNum) < 0)
            return false;
        
        String response = client.receiveResponse().trim();
        if (response != null)
                client.printResponse(response);
		
		client.closeSocket();
		
		if (expctResp != null)
			return response.equals (expctResp);
		
		return true;
	}
}
