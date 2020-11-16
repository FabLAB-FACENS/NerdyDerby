using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PopUpController : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    private void OnEnable()
    {
        StartCoroutine(DisableMe());
    }

    IEnumerator DisableMe()
    {
        yield return new WaitForSeconds(1);
        gameObject.SetActive(false);
        
    }
}
