using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Asteroid : MonoBehaviour
{
    public int points = 10;
    public GameObject explosion;
    public GameObject explosion_sound;

    [SerializeField]
    private Sprite[] asteroids;

    private float rotSpeed;
    private Rigidbody2D rb2D;

    void Awake() {
        GetComponent<SpriteRenderer>().sprite = asteroids[Random.Range(0, asteroids.Length)];
        gameObject.AddComponent<PolygonCollider2D>();
        GetComponent<PolygonCollider2D>().isTrigger = true;
        rotSpeed = Random.Range(15, 40);
        transform.localScale = Vector2.one * Random.Range(0.75f, 1.5f);
        rb2D = GetComponent<Rigidbody2D>();
    }

    void Start() {
        rb2D.velocity = -transform.right * Random.Range(5,12);
        //rb2D.velocity = new Vector2(Random.Range(-3, 3), Random.Range(-3, 3));
    }

    void Update()
    {
         transform.Rotate ( Vector3.forward * ( rotSpeed * Time.deltaTime ));
    }

    private void OnTriggerEnter2D(Collider2D collision)
    {
        if (collision.tag == "Bullet") {
            //Animation and destruction
            GameObject g = Instantiate(explosion, transform.position, Quaternion.identity);
            GameObject sound = Instantiate(explosion_sound, transform.position, Quaternion.identity);
            Destroy(g, 4f);
            Score_manager.score_manager.Add_score(points);
            Destroy(gameObject);
            Destroy(collision.gameObject);
        }
    }
}
