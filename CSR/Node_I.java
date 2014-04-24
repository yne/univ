import java.rmi.Remote;
import java.rmi.RemoteException;

public interface Node_I extends Remote {
	//getter/setter
	public int key() throws RemoteException;
	public Node_I pred() throws RemoteException;
	public void pred(Node_I n) throws RemoteException;
	public Node_I succ() throws RemoteException;
	public void succ(Node_I n) throws RemoteException;
	//utilities
	public Node_I findSucc(int key) throws RemoteException;
	public void stabilize() throws RemoteException;
	public void buildFT(int k) throws RemoteException;
	//chord function
	public String forward(int k,String msg) throws RemoteException;
	public String forwardFT(int k,String msg) throws RemoteException;
	public void   save(String key,String msg,int k) throws RemoteException;
	public String load(String key,int limit) throws RemoteException;
	//join/exit
	public void join() throws Exception;
	public void quit()throws Exception;
	//debug
	public String print() throws RemoteException;
}
