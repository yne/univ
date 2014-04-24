import java.rmi.RemoteException;
import java.rmi.registry.Registry;

public class Node_Stat extends Node{
	Node_Stat(Registry reg){
		super(reg);
	}
	Node_Stat(Registry r,int id){
		super(r,id);
	}
	public Node_I findSucc(int k)throws RemoteException {
		Stat.log("nbFindSucc");
		return super.findSucc(k);
	}
	public void quit()throws RemoteException {
		Stat.log("nbLookup");
		super.quit();
	}
	public void stabilize()throws RemoteException {
		Stat.log("nbStabilize");
		super.stabilize();
	}
	public void buildFT(int start_key) throws RemoteException{
		Stat.log("nbBuildFT");
		super.buildFT(start_key);
	}

	public String forwardFT(int k,String msg) throws RemoteException{
		Stat.log("nbForwardFT");
		return super.forwardFT(k,msg);
	}
	public String forward(int k,String msg) throws RemoteException{
		Stat.log("nbForward");
		return super.forward(k ,msg);
	}
	public void join() throws Exception{
		Stat.log("nbLookup");//lookup if bootstrap exist
		Stat.log("nbLookup");//create bootstrap or Node_X
		Stat.log("nbJoin");
		super.join();
    }
}
