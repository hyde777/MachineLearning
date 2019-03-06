using System;
using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using UnityEngine;

public class DllWrapperScript : MonoBehaviour
{
    [DllImport("Dll_C_SampleForUnity")]
    public static extern int return42();

    [DllImport("Dll_C_SampleForUnity")]
    public static extern double sum(double[] tab, int tabSize);

    [DllImport("Dll_C_SampleForUnity")]
    public static extern IntPtr create_array(int tabSize);

    [DllImport("Dll_C_SampleForUnity")]
    public static extern void delete_array(double[] tab);

    // Start is called before the first frame update
    void Start()
    {
        //foreach (var)
        Debug.Log(return42());

        var tab = new double[10];
        var rawArray = create_array(10);

        Marshal.Copy(rawArray, tab, 0, 10);

        foreach(double index in tab)
        {
            Debug.Log(index);
        }

        delete_array(tab);
        Debug.Log(tab.Length);
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
