using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Hover : MonoBehaviour
{
    private Vector3 initial_pos;

    void Start()
    {
        initial_pos = gameObject.transform.position + new Vector3(0, -0.6f, 0);
    }

     void Update()
     {
        gameObject.transform.position = initial_pos + new Vector3(0, 0.3f, 0) * Mathf.Cos(Time.time);
     }
}
