
using System;
using System.Runtime.InteropServices;
using UnityEngine;

public class DllWrapperScript : MonoBehaviour
{
	[DllImport("Dll_C_SampleForUnity")]
	public static extern int return42();
	
	//Tableau créé côté C#
	[DllImport("Dll_C_SampleForUnity")]
	public static extern double sum(double[] tab, int tabSize);

	//Tableau créé côté C++
	[DllImport("Dll_C_SampleForUnity")]
	public static extern IntPtr create_array(int tabSize);
	
	//Tableau créé côté C++
	[DllImport("Dll_C_SampleForUnity")]
	public static extern void delete_array(IntPtr tab);


	public Transform[] spheres;
	
	
	// Use this for initialization
	void Start () {

		foreach (var sphere in spheres)
		{
			Debug.Log(sphere.position);
		}
		
		Debug.Log(return42());
		
		Debug.Log(sum(new double[] {1,2,3,4,5}, 5));
		
		var managedArray = new double[10];
		var rawArray = create_array(10);
		
		Marshal.Copy(rawArray, managedArray, 0, 10);

		delete_array(rawArray);
		foreach (var elt in managedArray)
		{
			Debug.Log(elt);
		}
	}
}
