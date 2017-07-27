# Lazy
Lazy is another useful function that wraps an expensive function call to be invoked when first required:

```
fun readStringFromDatabase() : String = ... // expensive operation
val lazyString = lazy { readStringFromDatabase() }
```
The first time we require the result, we can access the value on the lazy reference. Only then will the wrapped function actually be invoked.

```
val string = lazyString.value
```
This is a common pattern seen in many languages and frameworks. The advantage of using this built-in function over rolling your own is that synchronization is taken care of for you. That is, if the value is requested twice, Kotlin will safely handle any race conditions by only executing the underlying function once.
