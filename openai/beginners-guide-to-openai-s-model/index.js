// index.js 

// Import required libraries
import dotenv from "dotenv";
import { Configuration, OpenAIApi } from "openai";
import readline from "readline";
import chalk from "chalk";

// Load environment variables
dotenv.config();

// Initialize the OpenAI API client
const openai = new OpenAIApi(
  new Configuration({ apiKey: process.env.OPENAI_API_KEY })
);

// Create a readline interface for user input
const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout
});

// Define an array to store the conversation messages
const GPTMessages = [];

// Set the model name; replace with other model names if needed
const modelName = "gpt-3.5-turbo" //"gpt-4";

// Define an async function to call the GPT API
const GPT = async (message) => {
  // Call the GPT API with the model, messages, and max tokens
  const response = await openai.createChatCompletion({
    model: modelName,
    messages: message,
    max_tokens: 100,
  });

  // Return the response content and the total number of tokens used
  return {
    content: response.data.choices[0].message.content,
    tokensUsed: response.data.usage.total_tokens,
  };
};

// Define a function to ask the user a question and handle their input
const askUserQuestion = (role) => {
  // Set the prompt text based on the role (system or user)
  const prompt = role === "system" ? "Enter system message: " : "Enter your question: ";

  // Ask the user a question and process their input
  rl.question(prompt, async (userInput) => {
    // Add the user's input to the GPTMessages array
    GPTMessages.push({ role: role, content: userInput });

    // If the input is a system message, ask the user for their question
    if (role === "system") {
      askUserQuestion("user");
    } else {
      // Call the GPT function with the current conversation messages
      const assistantResponse = await GPT(GPTMessages);

      // Add the assistant's response to the GPTMessages array
      GPTMessages.push({ role: "assistant", content: assistantResponse.content });

      // Display the assistant's response and the number of tokens used
      console.log(chalk.yellow("-----"));
      console.log(chalk.green("Assistant: "), assistantResponse.content);
      console.log(chalk.cyan("Tokens used: "), assistantResponse.tokensUsed);

      // Ask the user another question
      askUserQuestion("user");
    }
  });
};

// Display the model name and begin the conversation
console.log(`### I'm ${chalk.blue(modelName.toUpperCase())}. ####`);
askUserQuestion("system");
