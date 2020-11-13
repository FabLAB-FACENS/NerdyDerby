using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class RankingSort : MonoBehaviour
{
    public Transform itensContainer;
    
    
    // Start is called before the first frame update
    void Start()
    {
        foreach (Transform t in itensContainer)
        {
            Debug.Log(t.name);
        }   





    }

    // Update is called once per frame
    void Update()
    {
   
    }
}
