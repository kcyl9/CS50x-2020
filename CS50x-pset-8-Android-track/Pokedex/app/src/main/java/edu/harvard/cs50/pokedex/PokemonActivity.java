package edu.harvard.cs50.pokedex;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Context;
import android.content.SharedPreferences;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.AsyncTask;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;

import com.android.volley.Request;
import com.android.volley.RequestQueue;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.toolbox.JsonObjectRequest;
import com.android.volley.toolbox.Volley;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.IOException;
import java.net.URL;

public class PokemonActivity extends AppCompatActivity {
    private TextView nameTextView;
    private TextView numberTextView;
    private TextView type1TextView;
    private TextView type2TextView;
    private ImageView spriteImageView;
    private TextView descriptionTextView;
    private String url;
    private RequestQueue requestQueue;
    private boolean checkCatch;
    private String name;
    private SharedPreferences sharedPref;
    private Button catchButton;
    private String descriptionUrl;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_pokemon);

        requestQueue = Volley.newRequestQueue(getApplicationContext());
        url = getIntent().getStringExtra("url");
        nameTextView = findViewById(R.id.pokemon_name);
        numberTextView = findViewById(R.id.pokemon_number);
        type1TextView = findViewById(R.id.pokemon_type1);
        type2TextView = findViewById(R.id.pokemon_type2);
        spriteImageView = findViewById(R.id.pokemon_image);
        descriptionTextView = findViewById(R.id.description);
        sharedPref = getPreferences(Context.MODE_PRIVATE);
        catchButton = findViewById(R.id.catch_button);

        load();
    }

    public void load() {
        type1TextView.setText("");
        type2TextView.setText("");

        JsonObjectRequest request = new JsonObjectRequest(Request.Method.GET, url, null, new Response.Listener<JSONObject>() {
            @Override
            public void onResponse(JSONObject response) {
                try {
                    nameTextView.setText(response.getString("name"));
                    numberTextView.setText(String.format("#%03d", response.getInt("id")));
                    name = response.getString("name");
                    checkCatch = sharedPref.getBoolean(name, false);
                    if (checkCatch) {
                        catchButton.setText("Release");
                    }
                    else {
                        catchButton.setText("Catch");
                    }

                    JSONArray typeEntries = response.getJSONArray("types");
                    for (int i = 0; i < typeEntries.length(); i++) {
                        JSONObject typeEntry = typeEntries.getJSONObject(i);
                        int slot = typeEntry.getInt("slot");
                        String type = typeEntry.getJSONObject("type").getString("name");

                        if (slot == 1) {
                            type1TextView.setText(type);
                        }
                        else if (slot == 2) {
                            type2TextView.setText(type);
                        }
                    }

                    descriptionUrl = response.getJSONObject("species").getString("url");
                    JsonObjectRequest request1 = new JsonObjectRequest(Request.Method.GET, descriptionUrl, null, new Response.Listener<JSONObject>() {
                        @Override
                        public void onResponse(JSONObject response) {
                            try {
                                JSONArray descriptionEntries = response.getJSONArray("flavor_text_entries");
                                for (int i = 0; i < descriptionEntries.length(); i++) {
                                    JSONObject descriptionEntry = descriptionEntries.getJSONObject(i);
                                    String language = descriptionEntry.getJSONObject("language").getString("name");
                                    if (language.equals("en")) {
                                        descriptionTextView.setText(descriptionEntry.getString("flavor_text"));
                                        break;
                                    }
                                }
                            } catch (JSONException e) {
                                Log.e("cs50", "Pokemon description json error");
                            }
                        }
                    }, new Response.ErrorListener() {
                        @Override
                        public void onErrorResponse(VolleyError error) {
                            Log.e("cs50", "Pokemon description details error");
                        }
                    });
                    requestQueue.add(request1);
                    new DownloadSpriteTask().execute(response.getJSONObject("sprites").getString("front_default"));
                } catch (JSONException e) {
                    Log.e("cs50", "Pokemon json error", e);
                }
            }
        }, new Response.ErrorListener() {
            @Override
            public void onErrorResponse(VolleyError error) {
                Log.e("cs50", "Pokemon details error", error);
            }
        });

        requestQueue.add(request);
    }

    public void toggleCatch(View view) {
        checkCatch = !checkCatch;
        if (checkCatch) {
            catchButton.setText("Release");
        }
        else {
            catchButton.setText("Catch");
        }
        sharedPref.edit().putBoolean(name, checkCatch).commit();
    }

    private class DownloadSpriteTask extends AsyncTask<String, Void, Bitmap> {
        @Override
        protected Bitmap doInBackground(String... strings) {
            try {
                URL url = new URL(strings[0]);
                return BitmapFactory.decodeStream(url.openStream());
            }
            catch (IOException e) {
                Log.e("cs50", "Download sprite error", e);
                return null;
            }
        }

        @Override
        protected void onPostExecute(Bitmap bitmap) {
            spriteImageView.setImageBitmap(bitmap);
        }
    }
}
