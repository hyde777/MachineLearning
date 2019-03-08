
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using UnityEngine;

public class DllWrapperScript : MonoBehaviour
{
    /**
     * EXAMPLE.DLL
     **/

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


    /**
     * SOURCE.DLL
     **/

    //Création du model
    [DllImport("Dll_C_SampleForUnity")]
    public static extern IntPtr create_model(int nb_input);

    [DllImport("Dll_C_SampleForUnity")]
    public static extern void train_linear_classif(double[] model,
                                                    int size_model,
                                                    double[][] inputs,
                                                    int size_inputs,
                                                    int dimension_size,
                                                    double[] expected_outputs,
                                                    int expected_outputs_size,
                                                    double learning_rate,
                                                    int nb_epochs);

    [DllImport("Dll_C_SampleForUnity")]
    public static extern int sign_inference_linear_classif(double[] model, int modelSize, double input);
    

    public Transform[] spheres;
    public double[] model;


    // Use this for initialization
    void Start () {

        //int result = sign_inference_linear_classif(model, 20, spheres);

        //Debug.Log(return42());

        Debug.Log("Contenue du tableau de sphère");
        var spheres_xz = new double[25][];
        var spheres_y = new double[25];
        List<Tuple<int, Transform>> spheres2 = spheres.Select((x, i) => new Tuple<int, Transform>(i, x)).ToList();
        foreach (Tuple<int, Transform> sphere in spheres2)
        {
            var sphereO = sphere.Item2;
            int sphereIndex = sphere.Item1;
            Debug.Log(sphereO.position);

            spheres_xz[sphereIndex] = new double[] {sphereO.position.x, sphereO.position.z} ;
            spheres_y[sphereIndex] = sphereO.position.y;

        }

        var model = new double[25];
        var model_no_managed = create_model(25);

        Marshal.Copy(model_no_managed, model, 0, 25);

        Debug.Log("Contenu de mon model AVANT");
        foreach (var cell in model)
        {
            Debug.Log(cell);
        }

        train_linear_classif(model, 25, spheres_xz, 25, 2, spheres_y, 25, 10, 100);

        Debug.Log("Contenu de mon model APRES");
        foreach (var cell in model)
        {
            Debug.Log(cell);
        }

    }
}
