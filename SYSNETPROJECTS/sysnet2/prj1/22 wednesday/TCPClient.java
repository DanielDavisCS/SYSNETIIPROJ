import java.net.*;
import java.io.*;
import java.util.Scanner;
public class TCPClient{
    Socket sock;
    OutputStream sendStream;
    InputStream recvStream;
    String request;
    String response; 
    TCPClient( String server, int port ) throws IOException{
   	sock = new Socket(server, port);   
	sendStream = sock.getOutputStream();    
	recvStream = sock.getInputStream();   
    }
    
    public void makeRequest(){ 
	Scanner in = new Scanner(System.in);
	System.out.println("Message: ");
	request = in.nextLine();
    }

    public  void sendRequest(){    
	try{    	
	    byte[] sendBuff = new byte[request.length()];  
	    sendBuff = request.getBytes();    	
	    sendStream.write(sendBuff, 0, sendBuff.length);   
	}catch(IOException ex){    	
	    System.err.println("IOException in sendRequst"); 
	}   
    }   
    public void getResponse(){    
	try{    	
	    int dataSize;    
	    while((dataSize = recvStream.available()) == 0);   
	    byte[] recvBuff = new byte[dataSize];    	
	    recvStream.read(recvBuff, 0,dataSize);    	
	    response = new String(recvBuff,0,dataSize); 
	}catch (IOException ex){    	
	    System.err.println("IOException in sendResponse"); 
	}  
    }   
    
    public void useResponse(){   
	System.out.println("Response from server: " + response); 
    }
    
    public void close(){    
	try{    
	    sendStream.close();  
	    recvStream.close();    	
	    sock.close();    
	}catch(IOException ex){  
	    System.err.println("IOException in close"); 
	}   
    }      
    
    public static void main(String[] args)throws IOException {     
	if (args.length > 0) {	 
	    final int servPort = Integer.parseInt(args[1]);	
	    final String servName = args[0];
	    TCPClient client = new TCPClient(servName,servPort);  
	    client.makeRequest();  
	    client.sendRequest();    
	    client.getResponse();    
	    client.useResponse();    
	    client.close();    
	}
    }
}
